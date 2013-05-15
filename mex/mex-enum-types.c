
/* Generated data (by glib-mkenums) */

/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * Mex - Media Explorer
 *
 * Copyright © 2010 Intel Corporation.
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
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author:
 *   Damien Lespiau <damien.lespiau@intel.com>
 */

#include "mex-enum-types.h"

const gchar *
mex_enum_to_string (GType type,
                    gint  value)
{
    GEnumClass *enum_class;
    GEnumValue *enum_value;
    const gchar *val;

    enum_class = g_type_class_ref (type);
    enum_value = g_enum_get_value (enum_class, value);
    if (enum_value)
        val = enum_value->value_nick;
    else
        val = "<invalid enum value>";

    g_type_class_unref (enum_class);

    return val;
}

gboolean
mex_string_to_enum (GType        type,
                    const gchar *nick,
                    gint        *value)
{
    GEnumClass *enum_class;
    GEnumValue *enum_value;
    gboolean ret = FALSE;

    enum_class = g_type_class_ref (type);
    enum_value = g_enum_get_value_by_nick (enum_class, nick);
    if (enum_value) {
        if (value)
            *value = enum_value->value;
        ret = TRUE;
    }

    g_type_class_unref (enum_class);

    return ret;
}


/* enumerations from "../mex/mex-applet.h" */
#include "../mex/mex-applet.h"
GType
mex_applet_presentation_flags_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GFlagsValue values[] = {
        { MEX_APPLET_PRESENT_NONE, "MEX_APPLET_PRESENT_NONE", "none" },
        { MEX_APPLET_PRESENT_OPAQUE, "MEX_APPLET_PRESENT_OPAQUE", "opaque" },
        { MEX_APPLET_PRESENT_DIALOG, "MEX_APPLET_PRESENT_DIALOG", "dialog" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_flags_register_static (g_intern_static_string ("MexAppletPresentationFlags"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-content.h" */
#include "../mex/mex-content.h"
GType
mex_content_metadata_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_CONTENT_METADATA_NONE, "MEX_CONTENT_METADATA_NONE", "none" },
        { MEX_CONTENT_METADATA_SERIES_NAME, "MEX_CONTENT_METADATA_SERIES_NAME", "series-name" },
        { MEX_CONTENT_METADATA_TITLE, "MEX_CONTENT_METADATA_TITLE", "title" },
        { MEX_CONTENT_METADATA_SUB_TITLE, "MEX_CONTENT_METADATA_SUB_TITLE", "sub-title" },
        { MEX_CONTENT_METADATA_SEASON, "MEX_CONTENT_METADATA_SEASON", "season" },
        { MEX_CONTENT_METADATA_EPISODE, "MEX_CONTENT_METADATA_EPISODE", "episode" },
        { MEX_CONTENT_METADATA_STATION_ID, "MEX_CONTENT_METADATA_STATION_ID", "station-id" },
        { MEX_CONTENT_METADATA_STATION_LOGO, "MEX_CONTENT_METADATA_STATION_LOGO", "station-logo" },
        { MEX_CONTENT_METADATA_STILL, "MEX_CONTENT_METADATA_STILL", "still" },
        { MEX_CONTENT_METADATA_SYNOPSIS, "MEX_CONTENT_METADATA_SYNOPSIS", "synopsis" },
        { MEX_CONTENT_METADATA_YEAR, "MEX_CONTENT_METADATA_YEAR", "year" },
        { MEX_CONTENT_METADATA_DURATION, "MEX_CONTENT_METADATA_DURATION", "duration" },
        { MEX_CONTENT_METADATA_URL, "MEX_CONTENT_METADATA_URL", "url" },
        { MEX_CONTENT_METADATA_PLAYER, "MEX_CONTENT_METADATA_PLAYER", "player" },
        { MEX_CONTENT_METADATA_STREAM, "MEX_CONTENT_METADATA_STREAM", "stream" },
        { MEX_CONTENT_METADATA_STUDIO, "MEX_CONTENT_METADATA_STUDIO", "studio" },
        { MEX_CONTENT_METADATA_DIRECTOR, "MEX_CONTENT_METADATA_DIRECTOR", "director" },
        { MEX_CONTENT_METADATA_MIMETYPE, "MEX_CONTENT_METADATA_MIMETYPE", "mimetype" },
        { MEX_CONTENT_METADATA_COPYRIGHT, "MEX_CONTENT_METADATA_COPYRIGHT", "copyright" },
        { MEX_CONTENT_METADATA_COPYRIGHT_URL, "MEX_CONTENT_METADATA_COPYRIGHT_URL", "copyright-url" },
        { MEX_CONTENT_METADATA_PRICE, "MEX_CONTENT_METADATA_PRICE", "price" },
        { MEX_CONTENT_METADATA_PRICE_TYPE, "MEX_CONTENT_METADATA_PRICE_TYPE", "price-type" },
        { MEX_CONTENT_METADATA_PRICE_CURRENCY, "MEX_CONTENT_METADATA_PRICE_CURRENCY", "price-currency" },
        { MEX_CONTENT_METADATA_LICENSE, "MEX_CONTENT_METADATA_LICENSE", "license" },
        { MEX_CONTENT_METADATA_LICENSE_URL, "MEX_CONTENT_METADATA_LICENSE_URL", "license-url" },
        { MEX_CONTENT_METADATA_VALID_FROM, "MEX_CONTENT_METADATA_VALID_FROM", "valid-from" },
        { MEX_CONTENT_METADATA_VALID_UNTIL, "MEX_CONTENT_METADATA_VALID_UNTIL", "valid-until" },
        { MEX_CONTENT_METADATA_ID, "MEX_CONTENT_METADATA_ID", "id" },
        { MEX_CONTENT_METADATA_QUEUED, "MEX_CONTENT_METADATA_QUEUED", "queued" },
        { MEX_CONTENT_METADATA_DATE, "MEX_CONTENT_METADATA_DATE", "date" },
        { MEX_CONTENT_METADATA_CREATION_DATE, "MEX_CONTENT_METADATA_CREATION_DATE", "creation-date" },
        { MEX_CONTENT_METADATA_CAMERA_MODEL, "MEX_CONTENT_METADATA_CAMERA_MODEL", "camera-model" },
        { MEX_CONTENT_METADATA_ORIENTATION, "MEX_CONTENT_METADATA_ORIENTATION", "orientation" },
        { MEX_CONTENT_METADATA_FLASH_USED, "MEX_CONTENT_METADATA_FLASH_USED", "flash-used" },
        { MEX_CONTENT_METADATA_EXPOSURE_TIME, "MEX_CONTENT_METADATA_EXPOSURE_TIME", "exposure-time" },
        { MEX_CONTENT_METADATA_ISO_SPEED, "MEX_CONTENT_METADATA_ISO_SPEED", "iso-speed" },
        { MEX_CONTENT_METADATA_HEIGHT, "MEX_CONTENT_METADATA_HEIGHT", "height" },
        { MEX_CONTENT_METADATA_WIDTH, "MEX_CONTENT_METADATA_WIDTH", "width" },
        { MEX_CONTENT_METADATA_LAST_POSITION, "MEX_CONTENT_METADATA_LAST_POSITION", "last-position" },
        { MEX_CONTENT_METADATA_PLAY_COUNT, "MEX_CONTENT_METADATA_PLAY_COUNT", "play-count" },
        { MEX_CONTENT_METADATA_LAST_PLAYED_DATE, "MEX_CONTENT_METADATA_LAST_PLAYED_DATE", "last-played-date" },
        { MEX_CONTENT_METADATA_LAST_ID, "MEX_CONTENT_METADATA_LAST_ID", "last-id" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexContentMetadata"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-expander-box.h" */
#include "../mex/mex-expander-box.h"
GType
mex_expander_box_direction_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_EXPANDER_BOX_UP, "MEX_EXPANDER_BOX_UP", "up" },
        { MEX_EXPANDER_BOX_RIGHT, "MEX_EXPANDER_BOX_RIGHT", "right" },
        { MEX_EXPANDER_BOX_DOWN, "MEX_EXPANDER_BOX_DOWN", "down" },
        { MEX_EXPANDER_BOX_LEFT, "MEX_EXPANDER_BOX_LEFT", "left" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexExpanderBoxDirection"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-feed.h" */
#include "../mex/mex-feed.h"
GType
mex_feed_search_mode_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_FEED_SEARCH_MODE_OR, "MEX_FEED_SEARCH_MODE_OR", "or" },
        { MEX_FEED_SEARCH_MODE_AND, "MEX_FEED_SEARCH_MODE_AND", "and" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexFeedSearchMode"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-grilo-feed.h" */
#include "../mex/mex-grilo-feed.h"
GType
mex_grilo_operation_type_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_GRILO_FEED_OPERATION_NONE, "MEX_GRILO_FEED_OPERATION_NONE", "none" },
        { MEX_GRILO_FEED_OPERATION_BROWSE, "MEX_GRILO_FEED_OPERATION_BROWSE", "browse" },
        { MEX_GRILO_FEED_OPERATION_QUERY, "MEX_GRILO_FEED_OPERATION_QUERY", "query" },
        { MEX_GRILO_FEED_OPERATION_SEARCH, "MEX_GRILO_FEED_OPERATION_SEARCH", "search" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexGriloOperationType"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-info-panel.h" */
#include "../mex/mex-info-panel.h"
GType
mex_info_panel_mode_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_INFO_PANEL_MODE_FULL, "MEX_INFO_PANEL_MODE_FULL", "full" },
        { MEX_INFO_PANEL_MODE_SIMPLE, "MEX_INFO_PANEL_MODE_SIMPLE", "simple" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexInfoPanelMode"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-menu.h" */
#include "../mex/mex-menu.h"
GType
mex_menu_action_type_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_MENU_NONE, "MEX_MENU_NONE", "none" },
        { MEX_MENU_LEFT, "MEX_MENU_LEFT", "left" },
        { MEX_MENU_RIGHT, "MEX_MENU_RIGHT", "right" },
        { MEX_MENU_TOGGLE, "MEX_MENU_TOGGLE", "toggle" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexMenuActionType"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-shell.h" */
#include "../mex/mex-shell.h"
GType
mex_shell_direction_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { MEX_SHELL_DIRECTION_NONE, "MEX_SHELL_DIRECTION_NONE", "none" },
        { MEX_SHELL_DIRECTION_TOP, "MEX_SHELL_DIRECTION_TOP", "top" },
        { MEX_SHELL_DIRECTION_RIGHT, "MEX_SHELL_DIRECTION_RIGHT", "right" },
        { MEX_SHELL_DIRECTION_BOTTOM, "MEX_SHELL_DIRECTION_BOTTOM", "bottom" },
        { MEX_SHELL_DIRECTION_LEFT, "MEX_SHELL_DIRECTION_LEFT", "left" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("MexShellDirection"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* enumerations from "../mex/mex-utils.h" */
#include "../mex/mex-utils.h"
GType
mex_paint_texture_frame_flags_get_type (void)
{
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GFlagsValue values[] = {
        { MEX_TEXTURE_FRAME_EMPTY, "MEX_TEXTURE_FRAME_EMPTY", "empty" },
        { MEX_TEXTURE_FRAME_TOP_LEFT, "MEX_TEXTURE_FRAME_TOP_LEFT", "top-left" },
        { MEX_TEXTURE_FRAME_TOP, "MEX_TEXTURE_FRAME_TOP", "top" },
        { MEX_TEXTURE_FRAME_TOP_RIGHT, "MEX_TEXTURE_FRAME_TOP_RIGHT", "top-right" },
        { MEX_TEXTURE_FRAME_LEFT, "MEX_TEXTURE_FRAME_LEFT", "left" },
        { MEX_TEXTURE_FRAME_MIDDLE, "MEX_TEXTURE_FRAME_MIDDLE", "middle" },
        { MEX_TEXTURE_FRAME_RIGHT, "MEX_TEXTURE_FRAME_RIGHT", "right" },
        { MEX_TEXTURE_FRAME_BOTTOM_LEFT, "MEX_TEXTURE_FRAME_BOTTOM_LEFT", "bottom-left" },
        { MEX_TEXTURE_FRAME_BOTTOM, "MEX_TEXTURE_FRAME_BOTTOM", "bottom" },
        { MEX_TEXTURE_FRAME_BOTTOM_RIGHT, "MEX_TEXTURE_FRAME_BOTTOM_RIGHT", "bottom-right" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_flags_register_static (g_intern_static_string ("MexPaintTextureFrameFlags"), values);
      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* Generated data ends here */

