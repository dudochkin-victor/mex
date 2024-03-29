m4_define([mex_major], [0])
m4_define([mex_minor], [1])
m4_define([mex_micro], [0])

m4_define([mex_version], [mex_major.mex_minor.mex_micro])
m4_define([mex_api_version], [0.2])

# increase the interface age of 2 for each release
# set to 0 if the API changes
m4_define([mex_interface_age], [0])
m4_define([mex_binary_age], [m4_eval(100 * mex_minor + mex_micro)])

AC_PREREQ(2.53)
AC_INIT([mex], [mex_version], [http://www.intel.com])
AC_CONFIG_SRCDIR([mex/mex.h])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.9 foreign -Wno-portability no-define])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

LT_PREREQ([2.2.6])
LT_INIT([disable-static])

MEX_MAJOR_VERSION=mex_major
MEX_MINOR_VERSION=mex_minor
MEX_MICRO_VERSION=mex_micro
MEX_VERSION=mex_version
MEX_API_VERSION=mex_api_version
AC_SUBST(MEX_MAJOR_VERSION)
AC_SUBST(MEX_MINOR_VERSION)
AC_SUBST(MEX_MICRO_VERSION)
AC_SUBST(MEX_VERSION)
AC_SUBST(MEX_API_VERSION)

m4_define([lt_current], [m4_eval(100 * mex_minor + mex_micro - mex_interface_age)])
m4_define([lt_revision], [mex_interface_age])
m4_define([lt_age], [m4_eval(mex_binary_age - mex_interface_age)])
MEX_LT_CURRENT=lt_current
MEX_LT_REV=lt_revision
MEX_LT_AGE=lt_age
MEX_LT_VERSION="$MEX_LT_CURRENT:$MEX_LT_REV:$MEX_LT_AGE"
MEX_LT_LDFLAGS="-version-info $MEX_LT_VERSION"

AC_SUBST(MEX_LT_VERSION)
AC_SUBST(MEX_LT_LDFLAGS)

# i18n
AS_ALL_LINGUAS
IT_PROG_INTLTOOL([0.40.0], [no-xml])

GETTEXT_PACKAGE=mex
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE],
                   ["$GETTEXT_PACKAGE"],
                   [Gettext domain name])
AM_GLIB_GNU_GETTEXT
GLIB_DEFINE_LOCALEDIR(LOCALEDIR)

# check for programs
AC_PROG_CC
AM_PROG_CC_C_O

AM_PATH_GLIB_2_0

# check for headers
AC_HEADER_STDC

modules="glib-2.0 >= 2.26          \
         gio-2.0                   \
         gio-unix-2.0              \
         gdk-pixbuf-2.0            \
         libsoup-2.4         \
         mx-1.0 >= 1.1.11          \
         clutter-gst-1.0 >= 1.3.8  \
         rest-0.7                  \
         dbus-glib-1               \
         grilo-0.1 >= 0.1.14"

PKG_CHECK_EXISTS(libsoup-gnome-2.4,
                 [modules="$modules libsoup-gnome-2.4"
                 AC_DEFINE([HAVE_LIBSOUP_GNOME], [1], ["Defined if libsoup-gnome is available"])],
                 modules="$modules libsoup-2.4")

PKG_CHECK_MODULES(MEX, $modules)

PKG_CHECK_MODULES(GCONTROLLER, [gobject-2.0 >= 2.20])

AC_ARG_ENABLE([lirc],
              [AC_HELP_STRING([--enable-lirc],
                              [Enables LIRC remote control support])],
              [enable_lirc=yes],
              [enable_lirc=no])

if test "x$enable_lirc" = "xyes"; then
  AC_CHECK_LIB([lirc_client],
               [lirc_init],
               [AC_CHECK_HEADER([lirc/lirc_client.h],
                                [have_lirc=yes],
                                [have_lirc=no])],
               [have_lirc=no])

  if test "x$have_lirc" = "xyes"; then
    AC_DEFINE([HAVE_LIRC], [1], [LIRC support is enabled])
  else
    AC_MSG_ERROR([LIRC client support not available])
  fi

  MEX_LIRC_LIBS="-llirc_client"
  MEX_LIBS="${MEX_LIBS} ${MEX_LIRC_LIBS}"

  AC_SUBST(MEX_LIRC_LIBS)
fi

AM_CONDITIONAL([HAVE_LIRC], [test "x$enable_lirc" = "xyes"])

# marshals
AC_PATH_PROG([GLIB_GENMARSHAL], [glib-genmarshal])

GOBJECT_INTROSPECTION_CHECK([0.6.7])

# enable debug level
m4_define([debug_default],
          [m4_if(m4_eval(mex_minor % 2), [1], [yes], [minimum])])

AC_ARG_ENABLE([debug],
              [AC_HELP_STRING([--enable-debug=@<:@no/minimum/yes@:>@],
                              [Enables on debugging @<:@default=debug_default@:>@])],
              [],
              [enable_debug=debug_default])

AS_CASE([$enable_debug],
        [yes],
        [
          test "$cflags_set" = set || CFLAGS="$CFLAGS -g -O0"
          MEX_DEBUG_CFLAGS="-DMEX_ENABLE_DEBUG"
        ],

        [minimum],
        [
          MEX_DEBUG_CFLAGS="-DMEX_ENABLE_DEBUG -DG_DISABLE_CAST_CHECKS"
        ],

        [no],
        [
          MEX_DEBUG_CFLAGS="-DG_DISABLE_ASSERT -DG_DISABLE_CHECKS -DG_DISABLE_CAST_CHECKS"
        ],

        [AC_MSG_ERROR([Invalid value for --enable-debug])]
)

AC_SUBST(MEX_DEBUG_CFLAGS)

AC_ARG_WITH([player],
              [AC_HELP_STRING([--with-player=@<:@d-bus/clutter-gst/surface@:>@].
                              [Set mode for media playback @<:@default=clutter-gst@:>@])],
              [],
              [with_player=clutter-gst])

AS_CASE([$with_player],
        [clutter-gst],
        [
          AC_DEFINE([USE_PLAYER_CLUTTER_GST], 1, [Use "clutter-gst" for
                     playback])
        ],

        [d-bus],
        [
          AC_DEFINE([USE_PLAYER_DBUS], 1, [Use "d-bus" for playback])
        ],

        [surface],
        [
          AC_DEFINE([USE_PLAYER_SURFACE], 1, [Use "surface" for playback])
        ],

        [AC_MSG_ERROR([Invalid value for --with-player])]
)

AC_MSG_CHECKING([how to detect we are online])
AC_ARG_WITH([online],
            [AS_HELP_STRING([--with-online],
                            [how to check if we are online (always, connman, networkmanager, test)])],
                            [],
                            [with_online=always])

AS_CASE(["$with_online"],

        ["always"],
        [
        AC_MSG_RESULT([always])
        AC_DEFINE([WITH_ONLINE_ALWAYS], 1, [No online detection])
        ],

        ["connman"],
        [
        AC_MSG_RESULT([Connection Manager])
        AC_DEFINE([WITH_ONLINE_CONNMAN], 1, [ConnMan online detection])
        ],

        ["networkmanager"],
        [
        AC_MSG_RESULT([Network Manager])
        PKG_CHECK_MODULES(NM, libnm-glib >= 0.7)
        AC_DEFINE([WITH_ONLINE_NM], 1, [NM online detection])
        ],

        [AC_MSG_ERROR([Unknown argument "$with_online" to --with-online])]
)

# enable strict compiler flags
AC_ARG_ENABLE([maintainer-flags],
              [AC_HELP_STRING([--enable-maintainer-flags=@<:@no/yes@:>@],
                              [Use strict compiler flags @<:@default=maintainer_flags_default@:>@])],
              [],
              [enable_maintainer_flags=no])

AS_IF([test "x$enable_maintainer_flags" = "xyes"],
      [
        AS_COMPILER_FLAGS([MEX_MAINTAINER_CFLAGS],
                          ["-Wall -Wshadow -Wcast-align
                            -Wempty-body -Wformat-security
                            -Winit-self -Wmissing-declarations
                            -Wredundant-decls"])
      ],
      [
        AS_COMPILER_FLAGS([MEX_MAINTAINER_CFLAGS],
                          ["-Wall"])
      ]
)

AC_SUBST(MEX_MAINTAINER_CFLAGS)

# Compile tests
AC_ARG_ENABLE([tests],
              [AC_HELP_STRING([--enable-tests=@<:@no/yes@:>@],
                              [Build the unit tests default=no])],
              [],
              [enable_tests=no])

AM_CONDITIONAL([ENABLE_TESTS], [test "x$enable_tests" = "xyes"])
AS_IF([test "x$enable_tests" = "xyes"],
      AC_DEFINE([ENABLE_TESTS], [1], [Build unit tests]))

# Compile examples
AC_ARG_ENABLE([examples],
              [AC_HELP_STRING([--enable-examples=@<:@no/yes@:>@],
                              [Build the examples default=yes])],
              [],
              [enable_examples=yes])

AM_CONDITIONAL([ENABLE_EXAMPLES], [test "x$enable_examples" = "xyes"])
AS_IF([test "x$enable_examples" = "xyes"],
      AC_DEFINE([ENABLE_EXAMPLES], [1], [Build examples]))

# GTK Doc check
GTK_DOC_CHECK([1.13], [--flavour no-tmpl])
AM_CONDITIONAL([BUILD_GTK_DOC], [test "x$enable_gtk_doc" = "xyes"])

#
# Configuration applets
#

# Check the dependencies of rebinder
AC_ARG_ENABLE([rebinder],
              [AC_HELP_STRING([--enable-rebinder=@<:@yes/no@:>@],
                              [Enable the keyboard rebinder utility @<:@default=yes@:>@])],
              [],
              [enable_rebinder=yes])

AS_IF([test "x$enable_rebinder" = "xyes"],
      [PKG_CHECK_MODULES(REBINDER, [mx-1.0 dbus-glib-1 glib-2.0 gio-2.0 gudev-1.0 x11 xtst])
      AC_DEFINE(HAVE_REBINDER, [1], [Defined if the rebinder is available])],
      [])
AM_CONDITIONAL(ENABLE_REBINDER, test "x$enable_rebinder" = "xyes")

# Check the dependencies of network configuration ui
AC_ARG_ENABLE([networks],
              [AC_HELP_STRING([--enable-networks=@<:@yes/no@:>@],
                              [Enable the network configuration UI @<:@default=yes@:>@])],
              [],
              [enable_networks=yes])

AS_IF([test "x$enable_networks" = "xyes"],
      [PKG_CHECK_MODULES(NETWORKS, [glib-2.0 mx-1.0])],
      [])
AM_CONDITIONAL(ENABLE_NETWORKS, test "x$enable_networks" = "xyes")

# Check the dependencies of displayconf
AC_ARG_ENABLE([displayconf],
              [AC_HELP_STRING([--enable-displayconf=@<:@yes/no@:>@],
                              [Enable the displayconf utility @<:@default=yes@:>@])],
              [],
              [enable_displayconf=yes])
AS_IF([test "x$enable_displayconf" = "xyes"],
      [PKG_CHECK_MODULES(DISPLAYCONF, [glib-2.0 gnome-desktop-2.0 clutter-1.0])],
      [])
AM_CONDITIONAL(ENABLE_DISPLAYCONF, test "x$enable_displayconf" = "xyes")

#
# Shell
#

PKG_CHECK_MODULES(SHELL, [gio-unix-2.0 mx-1.0 clutter-1.0 glib-2.0 rest-0.7 dbus-glib-1])

PKG_CHECK_EXISTS(clutter-cex100-1.0, [AC_DEFINE(HAVE_CLUTTER_CEX100,
                                      [1],
                                      [Defined if we are on CEX100])],
                 [])

# Default list of plugins to compile
WITH_PLUGINS="search,queue,tracker"

# Provide a --with-plugins/--without-plugins configure option
AS_MEX_ARG_WITH_PLUGINS

# Declare all the plugins we have
AS_MEX_PLUGIN(library)
AS_MEX_PLUGIN(recommended)
AS_MEX_PLUGIN(search)
AS_MEX_PLUGIN(queue)
AS_MEX_PLUGIN(applications)
AS_MEX_PLUGIN(upnp)
AS_MEX_PLUGIN(tracker)

AC_CONFIG_FILES([
  Makefile
  build/Makefile
  mex/Makefile
  mex/glib-controller/Makefile
  player/Makefile
  data/Makefile
  data/appicons/Makefile
  examples/Makefile
  doc/Makefile
  doc/reference/Makefile
  doc/reference/mex/Makefile
  doc/reference/mex/mex-docs.xml
  applets/Makefile
  applets/displayconf/Makefile
  applets/rebinder/Makefile
  applets/networks/Makefile
  plugins/Makefile
  plugins/library/Makefile
  plugins/recommended/Makefile
  plugins/search/Makefile
  plugins/queue/Makefile
  plugins/applications/Makefile
  plugins/upnp/Makefile
  plugins/tracker/Makefile
  po/Makefile.in
  shell/Makefile
  tests/Makefile
  tools/Makefile
])

AC_OUTPUT

# Trim MEX_PLUGINS_SELECTED
MEX_PLUGINS_SELECTED=`echo $MEX_PLUGINS_SELECTED | tr -s ' ' | sed 's/^ //'`

echo ""
echo "media explorer - $VERSION"
echo ""
echo " • Build:"
echo "        Debugging flags   : ${enable_debug}"
echo "        Maintainer flags  : ${enable_maintainer_flags}"
echo "        Unit tests        : ${enable_tests}"
echo "        Examples          : ${enable_examples}"
echo "        Introspection data: ${enable_introspection}"
echo ""
echo " • Documentation:"
echo "        Build API Reference: ${enable_gtk_doc}"
echo ""
echo " • Plugins: ${MEX_PLUGINS_SELECTED}"
echo ""
echo " • Configuration Applets:"
echo "        Displayconf : ${enable_displayconf}"
echo "        Rebinder    : ${enable_rebinder}"
echo "        Networks    : ${enable_networks}"
echo ""
echo " • Extra:"
echo "        Enable LIRC support: ${enable_lirc}"
echo "        Media playback     : ${with_player}"
echo ""
