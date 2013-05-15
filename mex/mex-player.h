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


#ifndef __MEX_PLAYER_H__
#define __MEX_PLAYER_H__

#include <glib-object.h>
#include <clutter/clutter.h>

#include <mex/mex-content.h>

#include <mx/mx.h>

#include "mex-utils.h"

G_BEGIN_DECLS

#define MEX_TYPE_PLAYER mex_player_get_type()

#define MEX_PLAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), MEX_TYPE_PLAYER, MexPlayer))

#define MEX_PLAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), MEX_TYPE_PLAYER, MexPlayerClass))

#define MEX_IS_PLAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MEX_TYPE_PLAYER))

#define MEX_IS_PLAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), MEX_TYPE_PLAYER))

#define MEX_PLAYER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), MEX_TYPE_PLAYER, MexPlayerClass))

typedef struct _MexPlayer MexPlayer;
typedef struct _MexPlayerPrivate MexPlayerPrivate;
typedef struct _MexPlayerClass MexPlayerClass;


struct _MexPlayer
{
  MxStack parent;

  MexPlayerPrivate *priv;
};

struct _MexPlayerClass
{
  MxStackClass parent_class;
};

GType               mex_player_get_type           (void) G_GNUC_CONST;

MexPlayer *         mex_player_get_default        (void);
ClutterMedia *      mex_player_get_clutter_media  (MexPlayer *player);

void                mex_player_set_idle_mode      (MexPlayer *player,
                                                   gboolean   idle);
gboolean            mex_player_get_idle_mode      (MexPlayer *player);

void mex_player_set_sort_func (MexPlayer        *player,
                               GCompareDataFunc  func,
                               gpointer          userdata);

MexActorSortFunc mex_player_get_sort_func (MexPlayer *player,
                                           gpointer  *userdata);

void mex_player_stop (MexPlayer *player);
void mex_player_play (MexPlayer *player);
void mex_player_pause (MexPlayer *player);
void mex_player_forward (MexPlayer *player);
void mex_player_rewind (MexPlayer *player);
void mex_player_next (MexPlayer *player);
void mex_player_previous (MexPlayer *player);

G_END_DECLS

#endif /* __MEX_PLAYER_H__ */
