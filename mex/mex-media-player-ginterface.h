#include <glib-object.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

/**
 * MexMediaPlayerIface:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _MexMediaPlayerIface MexMediaPlayerIface;

/**
 * MexMediaPlayerIfaceClass:
 *
 * The class of MexMediaPlayerIface.
 */
typedef struct _MexMediaPlayerIfaceClass MexMediaPlayerIfaceClass;

GType mex_media_player_iface_get_type (void);
#define MEX_TYPE_MEDIA_PLAYER_IFACE \
  (mex_media_player_iface_get_type ())
#define MEX_MEDIA_PLAYER_IFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), MEX_TYPE_MEDIA_PLAYER_IFACE, MexMediaPlayerIface))
#define MEX_IS_MEDIA_PLAYER_IFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), MEX_TYPE_MEDIA_PLAYER_IFACE))
#define MEX_MEDIA_PLAYER_IFACE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), MEX_TYPE_MEDIA_PLAYER_IFACE, MexMediaPlayerIfaceClass))


typedef void (*mex_media_player_iface_set_audio_volume_impl) (MexMediaPlayerIface *self,
    gdouble in_volume,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_set_audio_volume (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_audio_volume_impl impl);
/**
 * mex_media_player_iface_return_from_set_audio_volume:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_set_audio_volume (DBusGMethodInvocation *context);
static inline void
mex_media_player_iface_return_from_set_audio_volume (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*mex_media_player_iface_get_audio_volume_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_audio_volume (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_audio_volume_impl impl);
/**
 * mex_media_player_iface_return_from_get_audio_volume:
 * @context: The D-Bus method invocation context
 * @out_volume: gdouble  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_audio_volume (DBusGMethodInvocation *context,
    gdouble out_volume);
static inline void
mex_media_player_iface_return_from_get_audio_volume (DBusGMethodInvocation *context,
    gdouble out_volume)
{
  dbus_g_method_return (context,
      out_volume);
}

typedef void (*mex_media_player_iface_set_uri_impl) (MexMediaPlayerIface *self,
    const gchar *in_uri,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_set_uri (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_uri_impl impl);
/**
 * mex_media_player_iface_return_from_set_uri:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_set_uri (DBusGMethodInvocation *context);
static inline void
mex_media_player_iface_return_from_set_uri (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*mex_media_player_iface_get_uri_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_uri (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_uri_impl impl);
/**
 * mex_media_player_iface_return_from_get_uri:
 * @context: The D-Bus method invocation context
 * @out_uri: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_uri (DBusGMethodInvocation *context,
    const gchar *out_uri);
static inline void
mex_media_player_iface_return_from_get_uri (DBusGMethodInvocation *context,
    const gchar *out_uri)
{
  dbus_g_method_return (context,
      out_uri);
}

typedef void (*mex_media_player_iface_set_playing_impl) (MexMediaPlayerIface *self,
    gboolean in_playing,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_set_playing (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_playing_impl impl);
/**
 * mex_media_player_iface_return_from_set_playing:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_set_playing (DBusGMethodInvocation *context);
static inline void
mex_media_player_iface_return_from_set_playing (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*mex_media_player_iface_get_playing_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_playing (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_playing_impl impl);
/**
 * mex_media_player_iface_return_from_get_playing:
 * @context: The D-Bus method invocation context
 * @out_playing: gboolean  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_playing (DBusGMethodInvocation *context,
    gboolean out_playing);
static inline void
mex_media_player_iface_return_from_get_playing (DBusGMethodInvocation *context,
    gboolean out_playing)
{
  dbus_g_method_return (context,
      out_playing);
}

typedef void (*mex_media_player_iface_set_progress_impl) (MexMediaPlayerIface *self,
    gdouble in_progress,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_set_progress (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_progress_impl impl);
/**
 * mex_media_player_iface_return_from_set_progress:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_set_progress (DBusGMethodInvocation *context);
static inline void
mex_media_player_iface_return_from_set_progress (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*mex_media_player_iface_get_progress_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_progress (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_progress_impl impl);
/**
 * mex_media_player_iface_return_from_get_progress:
 * @context: The D-Bus method invocation context
 * @out_progress: gdouble  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_progress (DBusGMethodInvocation *context,
    gdouble out_progress);
static inline void
mex_media_player_iface_return_from_get_progress (DBusGMethodInvocation *context,
    gdouble out_progress)
{
  dbus_g_method_return (context,
      out_progress);
}

typedef void (*mex_media_player_iface_get_duration_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_duration (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_duration_impl impl);
/**
 * mex_media_player_iface_return_from_get_duration:
 * @context: The D-Bus method invocation context
 * @out_duration: gdouble  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_duration (DBusGMethodInvocation *context,
    gdouble out_duration);
static inline void
mex_media_player_iface_return_from_get_duration (DBusGMethodInvocation *context,
    gdouble out_duration)
{
  dbus_g_method_return (context,
      out_duration);
}

typedef void (*mex_media_player_iface_get_can_seek_impl) (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context);
void mex_media_player_iface_implement_get_can_seek (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_can_seek_impl impl);
/**
 * mex_media_player_iface_return_from_get_can_seek:
 * @context: The D-Bus method invocation context
 * @out_seekable: gboolean  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_media_player_iface_return_from_get_can_seek (DBusGMethodInvocation *context,
    gboolean out_seekable);
static inline void
mex_media_player_iface_return_from_get_can_seek (DBusGMethodInvocation *context,
    gboolean out_seekable)
{
  dbus_g_method_return (context,
      out_seekable);
}

void mex_media_player_iface_emit_audio_volume_changed (gpointer instance,
    gdouble arg_volume);
void mex_media_player_iface_emit_playing_changed (gpointer instance,
    gboolean arg_playing);
void mex_media_player_iface_emit_progress_changed (gpointer instance,
    gdouble arg_progress);
void mex_media_player_iface_emit_duration_changed (gpointer instance,
    gdouble arg_duration);
void mex_media_player_iface_emit_error (gpointer instance,
    const gchar *arg_error);
void mex_media_player_iface_emit_buffer_fill_changed (gpointer instance,
    gdouble arg_buffer);
void mex_media_player_iface_emit_can_seek_changed (gpointer instance,
    gboolean arg_seekable);
void mex_media_player_iface_emit_eos (gpointer instance);


G_END_DECLS
