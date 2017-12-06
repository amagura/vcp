## Process this file with automake to produce Makefile.in

dist_doc_DATA = LICENSE AUTHORS INSTALL

dist_pkgdata_DATA = example.conf

SUBDIRS = src

DIST_SUBDIRS = $(SUBDIRS)

D2U = dos2unix

all-local:

anew: clean all

clean-local:
	$(RM) -r inst/usr
	$(RM) *.tar.gz

release: clean
	$(MAKE) DESTDIR="$$PWD/inst" install
	cd inst; \
	#$(RM) $(ZB_TARBALL) ;\
	#tar czf $(ZB_TARBALL) usr

refresh-check:
	cd src; \
	$(MAKE) $@

check-all:
	cd src; \
	$(MAKE) $@

iso:
	$(MAKE) dist
	genisoimage -o vcp.iso *.tar.gz
	mv vcp.iso ..

dos2unix:
	$(D2U) $(wildcard src/*)
