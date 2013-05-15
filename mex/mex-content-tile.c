/*
 * Mex - a media explorer
 *
 * Copyright © 2010, 2011 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>
 */


#include "mex-content-tile.h"

#include "mex-download-queue.h"
#include "mex-aspect-frame.h"
#include "mex-program.h"

static void mex_content_view_iface_init (MexContentViewIface *iface);
static void mx_focusable_iface_init (MxFocusableIface *iface);

G_DEFINE_TYPE_WITH_CODE (MexContentTile, mex_content_tile, MEX_TYPE_TILE,
                         G_IMPLEMENT_INTERFACE (MEX_TYPE_CONTENT_VIEW, mex_content_view_iface_init)
                         G_IMPLEMENT_INTERFACE (MX_TYPE_FOCUSABLE, mx_focusable_iface_init))

#define CONTENT_TILE_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((o), MEX_TYPE_CONTENT_TILE, MexContentTilePrivate))

enum
{
  PROP_THUMB_WIDTH = 1,
  PROP_THUMB_HEIGHT
};

struct _MexContentTilePrivate
{
  MexContent *content;
  guint changed_id;

  MexModel *model;

  ClutterActor *image;

  gint thumb_height;
  gint thumb_width;

  gpointer download_id;

  guint thumbnail_loaded : 1;
  guint image_set        : 1;
};

enum
{
  FOCUS_IN,
  FOCUS_OUT,

  LAST_SIGNAL
};

static gulong signals[LAST_SIGNAL] = { 0, };

static MxFocusable*
mex_content_tile_accept_focus (MxFocusable *focusable,
                               MxFocusHint  hint)
{
  clutter_actor_grab_key_focus (CLUTTER_ACTOR (focusable));

  g_signal_emit (focusable, signals[FOCUS_IN], 0);

  return focusable;
}

static MxFocusable*
mex_content_tile_move_focus (MxFocusable      *focusable,
                             MxFocusDirection  direction,
                             MxFocusable      *old_focus)
{
  g_signal_emit (focusable, signals[FOCUS_OUT], 0);

  return NULL;
}

static void
mx_focusable_iface_init (MxFocusableIface *iface)
{
  iface->accept_focus = mex_content_tile_accept_focus;
  iface->move_focus = mex_content_tile_move_focus;
}

static void
download_queue_completed (MexDownloadQueue *queue,
                          const gchar      *uri,
                          const gchar      *buffer,
                          gsize             count,
                          const GError     *error,
                          gpointer          user_data)
{
  MexContentTile *tile = MEX_CONTENT_TILE (user_data);
  MexContentTilePrivate *priv = tile->priv;
  GError *suberror = NULL;

  priv->download_id = NULL;
  priv->thumbnail_loaded = TRUE;

  if (error)
    {
      g_warning ("Error loading %s: %s", uri, error->message);
      return;
    }

  /* TODO: Find a way of not having to do a g_memdup here */
  if (!mx_image_set_from_buffer_at_size (MX_IMAGE (priv->image),
                                         g_memdup (buffer, count), count,
                                         (GDestroyNotify)g_free,
                                         priv->thumb_width,
                                         priv->thumb_height,
                                         &suberror))
    {
      g_warning ("Error loading %s: %s", uri, suberror->message);
      g_error_free (suberror);

      /* TODO: Maybe set a broken-image tile? */

      return;
    }

  priv->image_set = TRUE;
  clutter_actor_set_size (priv->image,
                          priv->thumb_width, priv->thumb_height);
}

static void
_update_title (MexContentTile *tile)
{
  MexContentTilePrivate *priv = tile->priv;
  const gchar *title;

  /* set title */
  title = mex_content_get_metadata (priv->content, MEX_CONTENT_METADATA_TITLE);

  mex_tile_set_label (MEX_TILE (tile), title);
}

static void
_update_thumbnail_from_image (MexContentTile *tile,
                              const gchar    *file)
{
  GError *error = NULL;

  MexContentTilePrivate *priv = tile->priv;

  if (!mx_image_set_from_file_at_size (MX_IMAGE (priv->image),
                                       file,
                                       -1,
                                       -1,
                                       &error))
    {
      g_warning ("Error loading %s: %s", file, error->message);
      g_error_free (error);

      return;
    }

  priv->image_set = TRUE;
}

static void
_reset_thumbnail (MexContentTile *tile)
{
  MexContentTilePrivate *priv = tile->priv;
  MexDownloadQueue *queue = mex_download_queue_get_default ();
  const gchar *mime = NULL;

  queue = mex_download_queue_get_default ();

  /* cancel any download already in progress */
  if (priv->download_id)
    {
      mex_download_queue_cancel (queue, priv->download_id);
      priv->download_id = NULL;
    }

  priv->thumbnail_loaded = FALSE;

  /* Load placeholder image */
  if (priv->content)
    mime = mex_content_get_metadata (priv->content,
                                     MEX_CONTENT_METADATA_MIMETYPE);

  if (mime && g_str_has_prefix (mime, "image/"))
    {
      _update_thumbnail_from_image (tile, PKGDATADIR "/thumb-image.png");
    }
  else if (mime && (g_str_has_prefix (mime, "video/") ||
                    g_str_equal (mime, "x-mex/media")))
    {
      _update_thumbnail_from_image (tile, PKGDATADIR "/thumb-video.png");
    }
  else if (mime && g_str_equal (mime, "x-grl/box"))
    {
      _update_thumbnail_from_image (tile, PKGDATADIR "/folder-tile.png");
    }
  else
    {
      mx_image_clear (MX_IMAGE (priv->image));

      /* Reset the height - really, we ought to reset the width and height,
       * but for all our use-cases, we want to keep the set width.
       */
      clutter_actor_set_height (priv->image, -1);
      priv->image_set = FALSE;

      return;
    }

  clutter_actor_set_size (priv->image,
                          priv->thumb_width, priv->thumb_height);
}

static void
_update_thumbnail (MexContentTile *tile)
{
  MexContentTilePrivate *priv = tile->priv;
  MexDownloadQueue *queue;
  const gchar *file;

  queue = mex_download_queue_get_default ();

  /* cancel any download already in progress */
  if (priv->download_id)
    {
      mex_download_queue_cancel (queue, priv->download_id);
      priv->download_id = NULL;
    }

  /* update thumbnail */
  file = mex_content_get_metadata (priv->content,
                                   MEX_CONTENT_METADATA_STILL);

  /* TODO: Display a spinner? */
  if (file)
    priv->download_id =
      mex_download_queue_enqueue (queue, file,
                                  download_queue_completed,
                                  tile);
  else
    priv->thumbnail_loaded = TRUE;
}

static void
_content_notify (MexContent     *content,
                 GParamSpec     *pspec,
                 MexContentTile *tile)
{
  MexContentTilePrivate *priv = tile->priv;
  const gchar *still_prop_name, *title_prop_name;

  still_prop_name = mex_content_get_property_name (MEX_CONTENT (priv->content),
                                                   MEX_CONTENT_METADATA_STILL);
  title_prop_name = mex_content_get_property_name (MEX_CONTENT (priv->content),
                                                   MEX_CONTENT_METADATA_TITLE);

  if (!g_strcmp0 (pspec->name, still_prop_name))
    {
      _reset_thumbnail (tile);
    }
  else if (!g_strcmp0 (pspec->name, title_prop_name))
    {
      _update_title (tile);
    }

}

static void
mex_content_tile_set_content (MexContentView *view,
                              MexContent     *content)
{
  MexContentTile *tile = MEX_CONTENT_TILE (view);
  MexContentTilePrivate *priv = tile->priv;

  if (priv->content == content)
    return;

  if (priv->changed_id)
    {
      g_signal_handler_disconnect (priv->content, priv->changed_id);
      priv->changed_id = 0;
    }

  if (priv->content)
    {
      g_object_unref (priv->content);
      priv->content = NULL;
    }

  if (!content)
    return;

  priv->content = g_object_ref_sink (content);

  /* Update title/thumbnail display */
  _update_title (tile);
  _reset_thumbnail (tile);

  /* TODO: use g_object_bind_property */
  priv->changed_id = g_signal_connect (priv->content,
                                       "notify",
                                       G_CALLBACK (_content_notify),
                                       view);
}

static MexContent*
mex_content_tile_get_content (MexContentView *view)
{
  MexContentTile *tile = MEX_CONTENT_TILE (view);
  MexContentTilePrivate *priv = tile->priv;

  return priv->content;
}

static void
mex_content_tile_set_context (MexContentView *view,
                              MexModel       *model)
{
  MexContentTile *tile = MEX_CONTENT_TILE (view);
  MexContentTilePrivate *priv = tile->priv;

  if (priv->model)
    g_object_unref (priv->model);

  priv->model = g_object_ref (model);
}

static MexModel*
mex_content_tile_get_context (MexContentView *view)
{
  MexContentTile *tile = MEX_CONTENT_TILE (view);
  MexContentTilePrivate *priv = tile->priv;

  return priv->model;
}

static void
mex_content_view_iface_init (MexContentViewIface *iface)
{
  iface->set_content = mex_content_tile_set_content;
  iface->get_content = mex_content_tile_get_content;

  iface->set_context = mex_content_tile_set_context;
  iface->get_context = mex_content_tile_get_context;
}


static void
mex_content_tile_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  MexContentTilePrivate *priv = MEX_CONTENT_TILE (object)->priv;

  switch (property_id)
    {
    case PROP_THUMB_WIDTH:
      g_value_set_int (value, priv->thumb_width);
      break;

    case PROP_THUMB_HEIGHT:
      g_value_set_int (value, priv->thumb_height);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
mex_content_tile_set_property (GObject      *object,
                               guint         property_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  MexContentTilePrivate *priv = MEX_CONTENT_TILE (object)->priv;

  switch (property_id)
    {
    case PROP_THUMB_WIDTH:
      priv->thumb_width = g_value_get_int (value);

      /* Ideally we'd use the image_set variable to determine if we set this,
       * but for all our use-cases, we always want the set thumbnail width.
       */
      clutter_actor_set_width (priv->image, priv->thumb_width);
      break;

    case PROP_THUMB_HEIGHT:
      priv->thumb_height = g_value_get_int (value);
      if (priv->image_set)
        clutter_actor_set_height (priv->image, priv->thumb_height);
      break;


    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }

}

static void
mex_content_tile_dispose (GObject *object)
{
  MexContentTilePrivate *priv = MEX_CONTENT_TILE (object)->priv;

  if (priv->content)
    {
      /* remove the reference to the MexContent and also disconnect the signal
       * handlers */
      mex_content_tile_set_content (MEX_CONTENT_VIEW (object), NULL);
    }

  if (priv->model)
    {
      g_object_unref (priv->model);
      priv->model = NULL;
    }

  if (priv->download_id)
    {
      MexDownloadQueue *dl_queue = mex_download_queue_get_default ();
      mex_download_queue_cancel (dl_queue, priv->download_id);
      priv->download_id = NULL;
    }

  G_OBJECT_CLASS (mex_content_tile_parent_class)->dispose (object);
}

static void
mex_content_tile_finalize (GObject *object)
{
  G_OBJECT_CLASS (mex_content_tile_parent_class)->finalize (object);
}

static void
mex_content_tile_paint (ClutterActor *actor)
{
  MexContentTilePrivate *priv = MEX_CONTENT_TILE (actor)->priv;

  if (priv->content && MEX_IS_PROGRAM (priv->content))
    _mex_program_complete (MEX_PROGRAM (priv->content));

  if (!priv->thumbnail_loaded && !priv->download_id)
    _update_thumbnail (MEX_CONTENT_TILE (actor));

  CLUTTER_ACTOR_CLASS (mex_content_tile_parent_class)->paint (actor);
}

static void
mex_content_tile_class_init (MexContentTileClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
  GParamSpec *pspec;

  g_type_class_add_private (klass, sizeof (MexContentTilePrivate));

  object_class->get_property = mex_content_tile_get_property;
  object_class->set_property = mex_content_tile_set_property;
  object_class->dispose = mex_content_tile_dispose;
  object_class->finalize = mex_content_tile_finalize;

  actor_class->paint = mex_content_tile_paint;

  pspec = g_param_spec_int ("thumb-width",
                            "Thumbnail width",
                            "Scale the width of the thumbnail while loading.",
                            -1, G_MAXINT, -1,
                            G_PARAM_READWRITE |
                            G_PARAM_STATIC_STRINGS);
  g_object_class_install_property (object_class, PROP_THUMB_WIDTH, pspec);

  pspec = g_param_spec_int ("thumb-height",
                            "Thumbnail height",
                            "Scale the height of the thumbnail while loading.",
                            -1, G_MAXINT, -1,
                            G_PARAM_READWRITE |
                            G_PARAM_STATIC_STRINGS);
  g_object_class_install_property (object_class, PROP_THUMB_HEIGHT, pspec);

  signals[FOCUS_IN] = g_signal_new ("focus-in",
                                    MEX_TYPE_CONTENT_TILE,
                                    G_SIGNAL_RUN_FIRST,
                                    0,
                                    NULL,
                                    NULL,
                                    g_cclosure_marshal_VOID__VOID,
                                    G_TYPE_NONE,
                                    0);

  signals[FOCUS_OUT] = g_signal_new ("focus-out",
                                     MEX_TYPE_CONTENT_TILE,
                                     G_SIGNAL_RUN_FIRST,
                                     0,
                                     NULL,
                                     NULL,
                                     g_cclosure_marshal_VOID__VOID,
                                     G_TYPE_NONE,
                                     0);
}

static void
mex_content_tile_init (MexContentTile *self)
{
  MexContentTilePrivate *priv;

  self->priv = priv = CONTENT_TILE_PRIVATE (self);

  priv->thumb_width = -1;
  priv->thumb_height = -1;

  priv->image = mx_image_new ();
  mx_image_set_load_async (MX_IMAGE (priv->image), TRUE);
  mx_image_set_scale_width_threshold (MX_IMAGE (priv->image), 128);
  mx_image_set_scale_height_threshold (MX_IMAGE (priv->image), 128);
  mx_image_set_scale_mode (MX_IMAGE (priv->image), MX_IMAGE_SCALE_CROP);

  mx_bin_set_child (MX_BIN (self), priv->image);
}

ClutterActor *
mex_content_tile_new (void)
{
  return g_object_new (MEX_TYPE_CONTENT_TILE, NULL);
}
