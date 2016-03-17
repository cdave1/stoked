AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir) -I$(top_srcdir)/include/stoked.h

AM_CFLAGS = $(GLOBAL_CFLAGS) -I$(top_srcdir)/include/stoked.h -I$(top_srcdir)/include/common.h

lib_LTLIBRARIES = libstoked.la
libstoked_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(LIBSTOKED_VERSION) -no-undefined
libstoked_la_SOURCES = \
		AbstractComponentPool.h \
		Component.h \
		Component.cpp \
		ComponentPool.h \
		Entity.h \
		Entity.cpp \
		EntityPool.h \
		EntityPool.cpp \
		EntitySystem.h \
		EntitySystem.cpp
