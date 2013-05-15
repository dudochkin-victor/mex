#include <glib-object.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

/**
 * MexRebinderControlIface:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _MexRebinderControlIface MexRebinderControlIface;

/**
 * MexRebinderControlIfaceClass:
 *
 * The class of MexRebinderControlIface.
 */
typedef struct _MexRebinderControlIfaceClass MexRebinderControlIfaceClass;

GType mex_rebinder_control_iface_get_type (void);
#define MEX_TYPE_REBINDER_CONTROL_IFACE \
  (mex_rebinder_control_iface_get_type ())
#define MEX_REBINDER_CONTROL_IFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), MEX_TYPE_REBINDER_CONTROL_IFACE, MexRebinderControlIface))
#define MEX_IS_REBINDER_CONTROL_IFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), MEX_TYPE_REBINDER_CONTROL_IFACE))
#define MEX_REBINDER_CONTROL_IFACE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), MEX_TYPE_REBINDER_CONTROL_IFACE, MexRebinderControlIfaceClass))


typedef void (*mex_rebinder_control_iface_quit_impl) (MexRebinderControlIface *self,
    DBusGMethodInvocation *context);
void mex_rebinder_control_iface_implement_quit (MexRebinderControlIfaceClass *klass, mex_rebinder_control_iface_quit_impl impl);
/**
 * mex_rebinder_control_iface_return_from_quit:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void mex_rebinder_control_iface_return_from_quit (DBusGMethodInvocation *context);
static inline void
mex_rebinder_control_iface_return_from_quit (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}



G_END_DECLS
