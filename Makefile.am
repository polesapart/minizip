lib_LTLIBRARIES = libminizip.la

if COND_DEMOS
bin_PROGRAMS = miniunzip minizip
endif

zlib_top_srcdir = $(top_srcdir)/../..
zlib_top_builddir = $(top_builddir)/../..

AM_CPPFLAGS = -I$(zlib_top_srcdir)
AM_LDFLAGS = -L$(zlib_top_builddir)

if WIN32
iowin32_src = iowin32.c
iowin32_h = iowin32.h
endif

libminizip_la_SOURCES = \
	ioapi.c \
	unzip.c \
	zip.c \
	${iowin32_src}

libminizip_la_LDFLAGS = $(AM_LDFLAGS) -version-info 1:0:0 -lz

minizip_includedir = $(includedir)/minizip
minizip_include_HEADERS = \
	crypt.h \
	ioapi.h \
	unzip.h \
	zip.h \
	${iowin32_h}

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = minizip.pc

EXTRA_PROGRAMS = miniunzip minizip

miniunzip_SOURCES = miniunz.c
miniunzip_LDADD = libminizip.la

minizip_SOURCES = minizip.c
minizip_LDADD = libminizip.la -lz

test:	miniunzip minizip
	@rm -f $(TEST_FILES)
	@cp README.md readme.txt
	@touch -t 200712301223.44 readme.txt
	./minizip test.zip readme.txt
	./miniunzip -l test.zip
	mv readme.txt readme.old
	./miniunzip test.zip
	@diff -q README.md readme.txt || echo "Test failed: files differ"
	@[[ "$$(stat -c %Y readme.txt)" = "$$(stat -c %Y readme.old)" ]] || echo "Test failed: timestamp not preserved"
	@rm -f $(TEST_FILES)

