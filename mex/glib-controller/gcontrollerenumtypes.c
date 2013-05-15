
/* Generated data (by glib-mkenums) */

#include "gcontrollerenumtypes.h"

/* enumerations from "../../mex/glib-controller/gcontrollertypes.h" */
#include "../../mex/glib-controller/gcontrollertypes.h"

GType
g_controller_action_get_type(void) {
  static volatile gsize g_enum_type_id__volatile = 0;

  if (g_once_init_enter (&g_enum_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { G_CONTROLLER_INVALID_ACTION, "G_CONTROLLER_INVALID_ACTION", "invalid-action" },
        { G_CONTROLLER_ADD, "G_CONTROLLER_ADD", "add" },
        { G_CONTROLLER_REMOVE, "G_CONTROLLER_REMOVE", "remove" },
        { G_CONTROLLER_UPDATE, "G_CONTROLLER_UPDATE", "update" },
        { G_CONTROLLER_CLEAR, "G_CONTROLLER_CLEAR", "clear" },
        { G_CONTROLLER_REPLACE, "G_CONTROLLER_REPLACE", "replace" },
        { 0, NULL, NULL }
      };
      GType g_enum_type_id;

      g_enum_type_id =
        g_enum_register_static (g_intern_static_string ("GControllerAction"), values);

      g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
    }

  return g_enum_type_id__volatile;
}

/* Generated data ends here */

