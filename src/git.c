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

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <string.h>
#include <stdbool.h>
#include <commoner.h>
#include <git2.h>
#include <dirent.h>

int gitrepo(char *cwd)
{
     int ret;
     char *tmp = strdup(cwd);
     catm(tmp, (PATH_MAX + 1), tmp, "/.git");
     git_libgit2_init();
     if (direxists(".git")) {
          ret = git_repository_open_ext(NULL, cwd, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
     } else {
          git_buf root {0};
          int err = git_repository_discover(&root, cwd, 0, NULL);
     }
     return true;
}
