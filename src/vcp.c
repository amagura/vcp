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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <libgen.h>
#include <git2.h>
#include <dirent.h>
#include <commoner.h>

#ifndef catm
# define catm(...) (concatm(__VA_ARGS__, (void *)NULL))
#endif

#ifndef catl
# define catl(...) (concatl(__VA_ARGS__, (void *)NULL))
#endif

#ifndef PATH_MAX
# ifdef LINUX_LIMITS_H
#  include <linux/limits.h>
# endif
#endif

enum repo_type {
     RT_NON = -1,
     RT_GIT = 0,
     RT_SVN = 1,
     RT_HG = 2,
};

/*int abspath(char *path)*/
/*{*/
     /*char buf[PATH_MAX + 1];*/
     /*char *ptr = realpath(*path, buf);*/
     /*[> FIXME: check errno!! <]*/
     /*return -1;*/
/*}*/

enum repo_type inrepo(void)
{
     char cwd[PATH_MAX + 1];
     if (getcwd(cwd, sizeof(cwd)) == NULL)
          return -9;

     catm(cwd, (PATH_MAX + 1), "/.git", (void *)NULL);

     DIR *dir = opendir(cwd);
     if (dir) {
          closedir(dir);
top_level_git:
          /* check if we're in a git repo */
          if (git_repository_open_ext(NULL, cwd, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL) == 0)
               return RT_GIT;
     } else if (ENOENT == errno) {
          git_buf root = {0};
          int error = git_repository_discover(&root, cwd, 0, NULL);


     return RT_NON;
}



int main(int argc, char **argv)
{
     /* FIXME
      * add option parsing
      */

     if (argc < 1)
          goto fail;

     int r = -9;
     /* FIXME: try to find a way to delay starting
      * the git library until we know we are
      * in a git repo, so that we don't have to
      * do unnecessary cleanup */
     git_libgit2_init();

     char cwd[PATH_MAX+1];
     if (getcwd(cwd, sizeof(cwd)) != NULL) {
          // print debug info
          r = inrepo(cwd);
          fprintf(stderr, "result from inrepo: '%d'\n", r);
          switch (r) {
               case RT_NON:
                    fprintf(stderr, "error\n");
                    goto fail;
                    break;
               case RT_GIT:
                    fprintf(stderr, "git repo\n");
                    break;
          }
     }
     return EXIT_SUCCESS;
fail:
     return EXIT_FAILURE;
}
