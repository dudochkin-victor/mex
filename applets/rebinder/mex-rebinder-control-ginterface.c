#include "mex-rebinder-control-ginterface.h"


static const DBusGObjectInfo _mex_rebinder_control_iface_object_info;

struct _MexRebinderControlIfaceClass {
    GTypeInterface parent_class;
    mex_rebinder_control_iface_quit_impl quit;
};

static void mex_rebinder_control_iface_base_init (gpointer klass);

GType
mex_rebinder_control_iface_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (MexRebinderControlIfaceClass),
        mex_rebinder_control_iface_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "MexRebinderControlIface", &info, 0);
    }

  return type;
}

/**
 * mex_rebinder_control_iface_quit_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Quit on interface com.meego.mex.Rebinder.
 */
static void
mex_rebinder_control_iface_quit (MexRebinderControlIface *self,
    DBusGMethodInvocation *context)
{
  mex_rebinder_control_iface_quit_impl impl = (MEX_REBINDER_CONTROL_IFACE_GET_CLASS (self)->quit);

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
 * mex_rebinder_control_iface_implement_quit:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Quit D-Bus method
 *
 * Register an implementation for the Quit method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
mex_rebinder_control_iface_implement_quit (MexRebinderControlIfaceClass *klass, mex_rebinder_control_iface_quit_impl impl)
{
  klass->quit = impl;
}

static inline void
mex_rebinder_control_iface_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (mex_rebinder_control_iface_get_type (),
      &_mex_rebinder_control_iface_object_info);

}
static void
mex_rebinder_control_iface_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      mex_rebinder_control_iface_base_init_once (klass);
    }
}
static const DBusGMethodInfo _mex_rebinder_control_iface_methods[] = {
  { (GCallback) mex_rebinder_control_iface_quit, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _mex_rebinder_control_iface_object_info = {
  0,
  _mex_rebinder_control_iface_methods,
  1,
"com.meego.mex.Rebinder\0Quit\0A\0\0\0",
"\0\0",
"\0\0",
};


