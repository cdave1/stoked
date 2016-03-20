AM_CPPFLAGS = -I$(top_srcdir)/include \
    -I$(top_srcdir)/src -I$(top_srcdir) \
    -I$(top_srcdir)/include/stoked.h

AM_CFLAGS = $(GLOBAL_CFLAGS) \
    -I$(top_srcdir)/include/stoked.h

bin_PROGRAMS = example

example_SOURCES = main.cpp
example_CFLAGS = -I$(top_srcdir) $(AM_CFLAGS)
example_LDFLAGS = $(AM_LDFLAGS)
example_LDADD = $(top_builddir)/src/libstoked.la
