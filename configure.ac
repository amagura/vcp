#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Vcp], [0.0.1], [amagura28@gmail.com],, [https://github.com/amagura/vcp/issues])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_FILES([Makefile
                 src/Makefile])

# Check for system extensions
AC_USE_SYSTEM_EXTENSIONS

# Check for targets
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_SEARCH_LIBS([concatm], [commoner],, AC_MSG_ERROR([libcommoner is required]))
AC_SEARCH_LIBS([git_libgit2_init], [git2],, AC_MSG_ERROR([libgit2 is required for git support]))

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h unistd.h git.h git2.h])
AC_CHECK_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([getcwd strdup])

# Options
AC_ARG_ENABLE([debug],
              [  --enable-debug		turn on debugging (default: disabled)],
              [case "${enableval}" in
               yes) debug=true ;;
               no) debug=false ;;
               *) AC_MSG_WARN([bad value '${enableval}' for --enable-debug]) ;;
             esac],[debug=no])

test "x$debug" = "xno" && no_debug=false
test "x$debug" = "xfalse" && no_debug=true

###############################
# Automake directives
###############################
AM_INIT_AUTOMAKE([foreign -Wall])
AM_CONDITIONAL([DEBUG], [test "x$debug" = "xtrue"])
AM_CONDITIONAL([NO_DEBUG], [test "x$debug" != "xtrue"])

AC_OUTPUT
