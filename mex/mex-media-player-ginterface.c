#include "mex-media-player-ginterface.h"

#include "mex-marshal.h"

static const DBusGObjectInfo _mex_media_player_iface_object_info;

struct _MexMediaPlayerIfaceClass {
    GTypeInterface parent_class;
    mex_media_player_iface_set_audio_volume_impl set_audio_volume;
    mex_media_player_iface_get_audio_volume_impl get_audio_volume;
    mex_media_player_iface_set_uri_impl set_uri;
    mex_media_player_iface_get_uri_impl get_uri;
    mex_media_player_iface_set_playing_impl set_playing;
    mex_media_player_iface_get_playing_impl get_playing;
    mex_media_player_iface_set_progress_impl set_progress;
    mex_media_player_iface_get_progress_impl get_progress;
    mex_media_player_iface_get_duration_impl get_duration;
    mex_media_player_iface_get_can_seek_impl get_can_seek;
};

enum {
    SIGNAL_MEDIA_PLAYER_IFACE_AudioVolumeChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_PlayingChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_ProgressChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_DurationChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_Error,
    SIGNAL_MEDIA_PLAYER_IFACE_BufferFillChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_CanSeekChanged,
    SIGNAL_MEDIA_PLAYER_IFACE_EOS,
    N_MEDIA_PLAYER_IFACE_SIGNALS
};
static guint media_player_iface_signals[N_MEDIA_PLAYER_IFACE_SIGNALS] = {0};

static void mex_media_player_iface_base_init (gpointer klass);

GType
mex_media_player_iface_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (MexMediaPlayerIfaceClass),
        mex_media_player_iface_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "MexMediaPlayerIface", &info, 0);
    }

  return type;
}

/**
 * mex_media_player_iface_set_audio_volume_impl:
 * @self: The object implementing this interface
 * @in_volume: gdouble  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetAudioVolume on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_set_audio_volume (MexMediaPlayerIface *self,
    gdouble in_volume,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_set_audio_volume_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->set_audio_volume);

  if (impl != NULL)
    {
      (impl) (self,
        in_volume,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_set_audio_volume:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetAudioVolume D-Bus method
 *
 * Register an implementation for the SetAudioVolume method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_set_audio_volume (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_audio_volume_impl impl)
{
  klass->set_audio_volume = impl;
}

/**
 * mex_media_player_iface_get_audio_volume_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAudioVolume on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_audio_volume (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_audio_volume_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_audio_volume);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_audio_volume:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAudioVolume D-Bus method
 *
 * Register an implementation for the GetAudioVolume method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_audio_volume (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_audio_volume_impl impl)
{
  klass->get_audio_volume = impl;
}

/**
 * mex_media_player_iface_set_uri_impl:
 * @self: The object implementing this interface
 * @in_uri: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetUri on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_set_uri (MexMediaPlayerIface *self,
    const gchar *in_uri,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_set_uri_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->set_uri);

  if (impl != NULL)
    {
      (impl) (self,
        in_uri,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_set_uri:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetUri D-Bus method
 *
 * Register an implementation for the SetUri method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_set_uri (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_uri_impl impl)
{
  klass->set_uri = impl;
}

/**
 * mex_media_player_iface_get_uri_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetUri on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_uri (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_uri_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_uri);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_uri:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetUri D-Bus method
 *
 * Register an implementation for the GetUri method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_uri (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_uri_impl impl)
{
  klass->get_uri = impl;
}

/**
 * mex_media_player_iface_set_playing_impl:
 * @self: The object implementing this interface
 * @in_playing: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetPlaying on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_set_playing (MexMediaPlayerIface *self,
    gboolean in_playing,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_set_playing_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->set_playing);

  if (impl != NULL)
    {
      (impl) (self,
        in_playing,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_set_playing:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetPlaying D-Bus method
 *
 * Register an implementation for the SetPlaying method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_set_playing (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_playing_impl impl)
{
  klass->set_playing = impl;
}

/**
 * mex_media_player_iface_get_playing_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetPlaying on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_playing (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_playing_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_playing);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_playing:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetPlaying D-Bus method
 *
 * Register an implementation for the GetPlaying method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_playing (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_playing_impl impl)
{
  klass->get_playing = impl;
}

/**
 * mex_media_player_iface_set_progress_impl:
 * @self: The object implementing this interface
 * @in_progress: gdouble  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetProgress on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_set_progress (MexMediaPlayerIface *self,
    gdouble in_progress,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_set_progress_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->set_progress);

  if (impl != NULL)
    {
      (impl) (self,
        in_progress,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_set_progress:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetProgress D-Bus method
 *
 * Register an implementation for the SetProgress method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_set_progress (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_set_progress_impl impl)
{
  klass->set_progress = impl;
}

/**
 * mex_media_player_iface_get_progress_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetProgress on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_progress (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_progress_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_progress);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_progress:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetProgress D-Bus method
 *
 * Register an implementation for the GetProgress method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_progress (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_progress_impl impl)
{
  klass->get_progress = impl;
}

/**
 * mex_media_player_iface_get_duration_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetDuration on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_duration (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_duration_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_duration);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_duration:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetDuration D-Bus method
 *
 * Register an implementation for the GetDuration method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_duration (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_duration_impl impl)
{
  klass->get_duration = impl;
}

/**
 * mex_media_player_iface_get_can_seek_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetCanSeek on interface com.meego.mex.MediaPlayer.
 */
static void
mex_media_player_iface_get_can_seek (MexMediaPlayerIface *self,
    DBusGMethodInvocation *context)
{
  mex_media_player_iface_get_can_seek_impl impl = (MEX_MEDIA_PLAYER_IFACE_GET_CLASS (self)->get_can_seek);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      GError e = { DBUS_GERROR, 
           DBUS_GERROR_UNKNOWN_METHOD,
           "Method not implemented" };

      dbus_g_method_return_error (context, &e);
    }
}

/**
 * mex_media_player_iface_implement_get_can_seek:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetCanSeek D-Bus method
 *
 * Register an implementation for the GetCanSeek method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_media_player_iface_implement_get_can_seek (MexMediaPlayerIfaceClass *klass, mex_media_player_iface_get_can_seek_impl impl)
{
  klass->get_can_seek = impl;
}

/**
 * mex_media_player_iface_emit_audio_volume_changed:
 * @instance: The object implementing this interface
 * @arg_volume: gdouble  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * AudioVolumeChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_audio_volume_changed (gpointer instance,
    gdouble arg_volume)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_AudioVolumeChanged],
      0,
      arg_volume);
}

/**
 * mex_media_player_iface_emit_playing_changed:
 * @instance: The object implementing this interface
 * @arg_playing: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PlayingChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_playing_changed (gpointer instance,
    gboolean arg_playing)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_PlayingChanged],
      0,
      arg_playing);
}

/**
 * mex_media_player_iface_emit_progress_changed:
 * @instance: The object implementing this interface
 * @arg_progress: gdouble  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ProgressChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_progress_changed (gpointer instance,
    gdouble arg_progress)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_ProgressChanged],
      0,
      arg_progress);
}

/**
 * mex_media_player_iface_emit_duration_changed:
 * @instance: The object implementing this interface
 * @arg_duration: gdouble  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * DurationChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_duration_changed (gpointer instance,
    gdouble arg_duration)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_DurationChanged],
      0,
      arg_duration);
}

/**
 * mex_media_player_iface_emit_error:
 * @instance: The object implementing this interface
 * @arg_error: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Error signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_error (gpointer instance,
    const gchar *arg_error)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_Error],
      0,
      arg_error);
}

/**
 * mex_media_player_iface_emit_buffer_fill_changed:
 * @instance: The object implementing this interface
 * @arg_buffer: gdouble  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * BufferFillChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_buffer_fill_changed (gpointer instance,
    gdouble arg_buffer)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_BufferFillChanged],
      0,
      arg_buffer);
}

/**
 * mex_media_player_iface_emit_can_seek_changed:
 * @instance: The object implementing this interface
 * @arg_seekable: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * CanSeekChanged signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_can_seek_changed (gpointer instance,
    gboolean arg_seekable)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_CanSeekChanged],
      0,
      arg_seekable);
}

/**
 * mex_media_player_iface_emit_eos:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * EOS signal on interface com.meego.mex.MediaPlayer.
 */
void
mex_media_player_iface_emit_eos (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, MEX_TYPE_MEDIA_PLAYER_IFACE));
  g_signal_emit (instance,
      media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_EOS],
      0);
}

static inline void
mex_media_player_iface_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (mex_media_player_iface_get_type (),
      &_mex_media_player_iface_object_info);

  /**
   * MexMediaPlayerIface::audio-volume-changed:
   * @arg_volume: gdouble  (FIXME, generate documentation)
   *
   * The AudioVolumeChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_AudioVolumeChanged] =
  g_signal_new ("audio-volume-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__DOUBLE,
      G_TYPE_NONE,
      1,
      G_TYPE_DOUBLE);

  /**
   * MexMediaPlayerIface::playing-changed:
   * @arg_playing: gboolean  (FIXME, generate documentation)
   *
   * The PlayingChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_PlayingChanged] =
  g_signal_new ("playing-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,
      1,
      G_TYPE_BOOLEAN);

  /**
   * MexMediaPlayerIface::progress-changed:
   * @arg_progress: gdouble  (FIXME, generate documentation)
   *
   * The ProgressChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_ProgressChanged] =
  g_signal_new ("progress-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__DOUBLE,
      G_TYPE_NONE,
      1,
      G_TYPE_DOUBLE);

  /**
   * MexMediaPlayerIface::duration-changed:
   * @arg_duration: gdouble  (FIXME, generate documentation)
   *
   * The DurationChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_DurationChanged] =
  g_signal_new ("duration-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__DOUBLE,
      G_TYPE_NONE,
      1,
      G_TYPE_DOUBLE);

  /**
   * MexMediaPlayerIface::error:
   * @arg_error: const gchar * (FIXME, generate documentation)
   *
   * The Error D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_Error] =
  g_signal_new ("error",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__STRING,
      G_TYPE_NONE,
      1,
      G_TYPE_STRING);

  /**
   * MexMediaPlayerIface::buffer-fill-changed:
   * @arg_buffer: gdouble  (FIXME, generate documentation)
   *
   * The BufferFillChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_BufferFillChanged] =
  g_signal_new ("buffer-fill-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__DOUBLE,
      G_TYPE_NONE,
      1,
      G_TYPE_DOUBLE);

  /**
   * MexMediaPlayerIface::can-seek-changed:
   * @arg_seekable: gboolean  (FIXME, generate documentation)
   *
   * The CanSeekChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_CanSeekChanged] =
  g_signal_new ("can-seek-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,
      1,
      G_TYPE_BOOLEAN);

  /**
   * MexMediaPlayerIface::e-os:
   *
   * The EOS D-Bus signal is emitted whenever this GObject signal is.
   */
  media_player_iface_signals[SIGNAL_MEDIA_PLAYER_IFACE_EOS] =
  g_signal_new ("e-os",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

}
static void
mex_media_player_iface_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      mex_media_player_iface_base_init_once (klass);
    }
}
static const DBusGMethodInfo _mex_media_player_iface_methods[] = {
  { (GCallback) mex_media_player_iface_set_audio_volume, mex_marshal_VOID__DOUBLE_POINTER, 0 },
  { (GCallback) mex_media_player_iface_get_audio_volume, g_cclosure_marshal_VOID__POINTER, 55 },
  { (GCallback) mex_media_player_iface_set_uri, mex_marshal_VOID__STRING_POINTER, 114 },
  { (GCallback) mex_media_player_iface_get_uri, g_cclosure_marshal_VOID__POINTER, 158 },
  { (GCallback) mex_media_player_iface_set_playing, mex_marshal_VOID__BOOLEAN_POINTER, 206 },
  { (GCallback) mex_media_player_iface_get_playing, g_cclosure_marshal_VOID__POINTER, 258 },
  { (GCallback) mex_media_player_iface_set_progress, mex_marshal_VOID__DOUBLE_POINTER, 314 },
  { (GCallback) mex_media_player_iface_get_progress, g_cclosure_marshal_VOID__POINTER, 368 },
  { (GCallback) mex_media_player_iface_get_duration, g_cclosure_marshal_VOID__POINTER, 426 },
  { (GCallback) mex_media_player_iface_get_can_seek, g_cclosure_marshal_VOID__POINTER, 484 },
};

static const DBusGObjectInfo _mex_media_player_iface_object_info = {
  0,
  _mex_media_player_iface_methods,
  10,
"com.meego.mex.MediaPlayer\0SetAudioVolume\0A\0volume\0I\0d\0\0com.meego.mex.MediaPlayer\0GetAudioVolume\0A\0volume\0O\0F\0N\0d\0\0com.meego.mex.MediaPlayer\0SetUri\0A\0uri\0I\0s\0\0com.meego.mex.MediaPlayer\0GetUri\0A\0uri\0O\0F\0N\0s\0\0com.meego.mex.MediaPlayer\0SetPlaying\0A\0playing\0I\0b\0\0com.meego.mex.MediaPlayer\0GetPlaying\0A\0playing\0O\0F\0N\0b\0\0com.meego.mex.MediaPlayer\0SetProgress\0A\0progress\0I\0d\0\0com.meego.mex.MediaPlayer\0GetProgress\0A\0progress\0O\0F\0N\0d\0\0com.meego.mex.MediaPlayer\0GetDuration\0A\0duration\0O\0F\0N\0d\0\0com.meego.mex.MediaPlayer\0GetCanSeek\0A\0seekable\0O\0F\0N\0b\0\0\0",
"com.meego.mex.MediaPlayer\0AudioVolumeChanged\0com.meego.mex.MediaPlayer\0PlayingChanged\0com.meego.mex.MediaPlayer\0ProgressChanged\0com.meego.mex.MediaPlayer\0DurationChanged\0com.meego.mex.MediaPlayer\0Error\0com.meego.mex.MediaPlayer\0BufferFillChanged\0com.meego.mex.MediaPlayer\0CanSeekChanged\0com.meego.mex.MediaPlayer\0EOS\0\0",
"\0\0",
};


