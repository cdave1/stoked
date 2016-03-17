#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Stoked], [1], [david@davidpetrie.com])
AC_CONFIG_SRCDIR([include/stoked.h])
AM_INIT_AUTOMAKE([dist-bzip2 no-dist-gzip check-news])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Enable c++11
# AX_CHECK_COMPILE_FLAG([-std=c++0x], [CXXFLAGS=`$CXXFLAGS -std=c++0x`])

# Checks for programs.
# AC_PROG_CXX="$CXXFLAGS -std=c++0x"
AC_PROG_CXX
AC_PROG_CC

LIBSTOKED_VERSION=1

AC_SUBST(LIBSTOKED_VERSION)

LT_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_C_CONST
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
