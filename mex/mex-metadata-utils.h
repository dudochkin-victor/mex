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

#ifndef __MEX_METADATA_UTILS_H__
#define __MEX_METADATA_UTILS_H__

#include <glib.h>

void mex_metadata_from_uri (const gchar *uri,
                            gchar      **title,
                            gchar      **showname,
                            GDate      **date,
                            gint        *season,
                            gint        *episode);

gchar * mex_metadata_humanise_duration (const gchar *duration);

gchar *mex_metadata_humanise_date (const gchar *iso8601_date);

gchar *mex_metadata_humanise_time (const gchar *time);

#endif
