/*
 * Mex - a media explorer
 *
 * Copyright © , 2010, 2011 Intel Corporation.
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

/* mex-library-plugin.c */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mex-library-plugin.h"
#include <mex/mex-grilo-feed.h>

#include <glib/gi18n.h>

static void mex_model_provider_iface_init (MexModelProviderInterface *iface);

G_DEFINE_TYPE_WITH_CODE (MexLibraryPlugin, mex_library_plugin,
                         G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (MEX_TYPE_MODEL_PROVIDER,
                                                mex_model_provider_iface_init))

#define LIBRARY_PLUGIN_PRIVATE(o) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((o), MEX_TYPE_LIBRARY_PLUGIN, MexLibraryPluginPrivate))

struct _MexLibraryPluginPrivate
{
  GList *models;
};


static void
mex_library_plugin_dispose (GObject *object)
{
  MexLibraryPluginPrivate *priv = MEX_LIBRARY_PLUGIN (object)->priv;

  while (priv->models)
    {
      MexModelInfo *info = priv->models->data;
      mex_model_info_free (info);
      priv->models = g_list_delete_link (priv->models, priv->models);
    }

  G_OBJECT_CLASS (mex_library_plugin_parent_class)->dispose (object);
}

static void
mex_library_plugin_finalize (GObject *object)
{
  G_OBJECT_CLASS (mex_library_plugin_parent_class)->finalize (object);
}

static void
mex_library_plugin_class_init (MexLibraryPluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (MexLibraryPluginPrivate));

  object_class->dispose = mex_library_plugin_dispose;
  object_class->finalize = mex_library_plugin_finalize;
}

static const GList *
mex_library_plugin_get_models (MexModelProvider *self)
{
  MexLibraryPluginPrivate *priv = MEX_LIBRARY_PLUGIN (self)->priv;
  return priv->models;
}

static void
mex_model_provider_iface_init (MexModelProviderInterface *iface)
{
  iface->get_models = mex_library_plugin_get_models;
}

static GrlMedia *
mex_library_plugin_get_box_for_path (GrlMediaSource *source,
                                     const GList    *keys,
                                     const gchar    *path)
{
  gchar *uri;
  GrlMedia *box;

  GError *error = NULL;

  uri = g_filename_to_uri (path, NULL, &error);
  if (!uri)
    {
      g_warning ("Error converting path to uri: %s", error->message);
      g_error_free (error);
      return NULL;
    }

  box = grl_media_source_get_media_from_uri_sync (source, uri, keys,
                                                  GRL_RESOLVE_FAST_ONLY,
                                                  &error);
  g_free (uri);

  if (!box)
    {
      g_warning ("Error getting media from uri: %s", error->message);
      g_error_free (error);
      return NULL;
    }

  return box;
}

static void
mex_library_plugin_init (MexLibraryPlugin *self)
{
  GrlMediaPlugin *plugin;
  GrlPluginRegistry *registry;

  MexLibraryPluginPrivate *priv = self->priv =
    LIBRARY_PLUGIN_PRIVATE (self);

  registry = grl_plugin_registry_get_default ();

  plugin = grl_plugin_registry_lookup_source (registry, "grl-filesystem");
  if (plugin)
    {
      GList *query_keys;
      MexFeed *feed;
      GrlMedia *box;
      const gchar *path;
      MexModelInfo *video_info, *photo_info;

      query_keys = grl_metadata_key_list_new (GRL_METADATA_KEY_ID,
                                              GRL_METADATA_KEY_TITLE,
                                              GRL_METADATA_KEY_MIME,
                                              GRL_METADATA_KEY_URL,
                                              GRL_METADATA_KEY_DATE,
                                              NULL);

      /* Add the videos model */
      path = g_get_user_special_dir (G_USER_DIRECTORY_VIDEOS);
      box = mex_library_plugin_get_box_for_path (GRL_MEDIA_SOURCE (plugin),
                                                 query_keys, path);

      if (box)
        {
          GList *metadata_keys =
            grl_metadata_key_list_new (GRL_METADATA_KEY_ID,
                                       GRL_METADATA_KEY_DESCRIPTION,
                                       GRL_METADATA_KEY_DURATION,
                                       GRL_METADATA_KEY_THUMBNAIL,
                                       GRL_METADATA_KEY_WIDTH,
                                       GRL_METADATA_KEY_HEIGHT,
                                       NULL);

          feed = mex_grilo_feed_new (GRL_MEDIA_SOURCE (plugin),
                                     query_keys, metadata_keys, box);
          g_object_set (feed, "icon-name", "icon-library",
                        "placeholder-text", "No videos found", NULL);


          mex_grilo_feed_browse (MEX_GRILO_FEED (feed), 0, G_MAXINT);

          video_info = mex_model_info_new_with_sort_funcs (MEX_MODEL (feed),
                                                           "videos", 0);
          priv->models = g_list_append (priv->models, video_info);
          g_object_unref (feed);
          g_list_free (metadata_keys);
        }

      /* Add the photos model */
      path = g_get_user_special_dir (G_USER_DIRECTORY_PICTURES);
      box = mex_library_plugin_get_box_for_path (GRL_MEDIA_SOURCE (plugin),
                                                 query_keys, path);

      if (box)
        {
          GList *metadata_keys =
            grl_metadata_key_list_new (GRL_METADATA_KEY_ID,
                                       GRL_METADATA_KEY_DESCRIPTION,
                                       GRL_METADATA_KEY_THUMBNAIL,
                                       GRL_METADATA_KEY_WIDTH,
                                       GRL_METADATA_KEY_HEIGHT,
                                       NULL);

          feed = mex_grilo_feed_new (GRL_MEDIA_SOURCE (plugin),
                                     query_keys, metadata_keys, box);
          g_object_set (feed, "icon-name", "icon-library",
                        "placeholder-text", "No pictures found", NULL);

          mex_grilo_feed_browse (MEX_GRILO_FEED (feed), 0, G_MAXINT);

          photo_info = mex_model_info_new_with_sort_funcs (MEX_MODEL (feed),
                                                           "pictures", 0);
          priv->models = g_list_append (priv->models, photo_info);
          g_object_unref (feed);
          g_list_free (metadata_keys);
        }

      g_list_free (query_keys);
    }
  else
    g_warning ("Filesystem plugin not found");
}

G_MODULE_EXPORT const GType
mex_get_plugin_type (void)
{
  return MEX_TYPE_LIBRARY_PLUGIN;
}
