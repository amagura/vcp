/****
Copyright 2017 Alexej Magura

This file is a part of Vcp

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****/
#ifndef VCP_GIT_H_GUARD
# define VCP_GIT_H_GUARD 1
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
so that C++ compilers don't mangle their names.  Use END_C_DECLS at
the end of C declarations. */
# undef BEGIN_C_DECLS
# undef END_C_DECLS
# ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS }
# else
#  define BEGIN_C_DECLS /* empty */
#  define END_C_DECLS /* empty */
# endif

/* PARAMS is a macro used to wrap function prototypes, so that
  compilers that don't understand ANSI C prototypes still work,
  and ANSI C compilers can issue warnings about type mismatches. */
# undef PARAMS
# if defined (__STDC__) || defined (_AIX) \
       || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
       || defined(WIN32) || defined(__cplusplus)
#  define PARAMS(protos) protos
# else
#  define PARAMS(protos) ()
# endif

# define com_neko(COM_F, ...)				\
     do {						\
	  fprintf(stderr,				\
		  "\n%s{neko-chan}%s(%s)(%s)(%d)\n",	\
		  "\033[91m❤\033[0m",		\
		  "\033[91m❤\033[0m",		\
		  __FILE__, __FUNCTION__, __LINE__);	\
	  fprintf(stderr, "%s%s%s, %s%s%s~\n",		\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[0m",			\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[33ma\033[0m");		\
	  fprintf(stderr, (COM_F), ##__VA_ARGS__);	\
	  fprintf(stderr, "\n");			\
     } while(0)

BEGIN_C_DECLS
#if HAVE_CONFIG_H
# include <config.h>
#endif


int gitrepo PARAMS((char *cwd));

END_C_DECLS

#endif /* VCP_GIT_H_GUARD */
