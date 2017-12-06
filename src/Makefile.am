## Process this file with automake to produce Makefile.in

bin_PROGRAMS = vcp
vcp_SOURCES = vcp.c git.c svn.c hg.c

AM_CFLAGS =
AM_LDFLAGS =
AM_CPPFLAGS =

AM_CFLAGS += -O2 -Wall -Wextra
# I probably don't need to define HAVE_CONFIG_H, but I'm not sure what else to do.
AM_CPPFLAGS += -DHAVE_CONFIG_H=1 -I$(top_srcdir)

#if DEBUG
#AM_CFLAGS += -g -ggdb
#AM_CPPFLAGS += -DCOM_DEBUG=1
#endif

#if !DEBUG
#if NO_DEBUG
#AM_CPPFLAGS += -DCOM_DEBUG=0
#endif
#endif

#if NATIVE
#if !GENERIC
#AM_CFLAGS += -march=native -mtune=native
#endif
#endif

#if GENERIC
#if CPU_KNOWN
#AM_CFLAGS += -mtune=generic-$(CPUTYPE)
#else
#AM_CFLAGS += -mtune=generic
#endif
#endif

vcp_CFLAGS = $(AM_CFLAGS)
vcp_CPPFLAGS = -DCOM_PROGNAME=\"vcp\" $(AM_CPPFLAGS)

.PHONY: valgrind lint
all-local:

move-local: $(bin_PROGRAMS)
	for file in $?; do mv "$$file" ../../; done

clean-local: tidy-local

lint:
	for f in $(vcp_SOURCES); do cppcheck --enable=all $$f; echo; done

valgrind: clean $(bin_PROGRAMS)
	for f in $(bin_PROGRAMS); do \
		test "$$f" = "gzbatt" || \
		$@ --leak-check=full --show-leak-kinds=all --track-origins=yes ./"$$f"; \
		echo; \
		echo; \
	done

vvalgrind: clean $(bin_PROGRAMS)
	for f in $(bin_PROGRAMS); do \
		test "$$f" = "gzbatt" || \
		valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./"$$f"; \
		echo; \
		echo; \
	done

mtrace: $(bin_PROGRAMS)
	for f in $^; do MALLOC_TRACE=./mtrace.txt ./$$f; mtrace ./$$f ./mtrace.txt; echo; cat mtrace.txt; echo; echo; done

expand:
	$(CC) $(AM_CFLAGS) $(AM_CPPFLAGS) -E $(vcp_SOURCES)

check-local: $(bin_PROGRAMS) refresh-check
	cd test; \
	./configure

refresh-check:
	cd test; \
	autoconf

asm: $(vcp_SOURCES:.c=.s) $(bin_PROGRAMS)
	for f in $(vcp_SOURCES:.c=.o); do objdump --file-start-context -slS "$$f" > "$${f//.*/.od}"; done

.c.s:
	$(CC) $(AM_CFLAGS) $(AM_CPPFLAGS) -S $<

.pyx.c:
	$(CC) -E $(vcp_CPPFLAGS) -o $(@:.c=.co) $< $(top_srcdir)/config.h
	$(CYTHON) --embed -p -2 -Wextra -o $@ $(@:.c=.co)

tidy-local:
	$(RM) *.o || true
	$(RM) *.od || true
	$(RM) *.py || true
	$(RM) *.pyc || true
	$(RM) no_common.h || true

anew: clean all
ready: clean all tidy-local
null: clean all clean
void: null

prod:
	cd "$(top_srcdir)"; \
	autoconf && \
	./configure --disable-debug --disable-testdir --enable-static --disable-native --enable-generic && \
	$(MAKE)

no-debug:
	cd "$(top_srcdir)"; \
	autoconf && \
	./configure --disable-debug --enable-generic --disable-native && \
	$(MAKE)

check-configure: refresh-check
	cd test && \
	cat configure | less

check-all: $(bin_PROGRAMS) gzbatt refresh-check
	cd test && \
	./configure --with-gtk2

debug:
	cd "$(top_srcdir)"; \
	autoconf && \
	./configure --enable-debug --enable-testdir --enable-generic --disable-native && \
	$(MAKE)
