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

#include "git.h"
#include <commoner.h>

#include <string.h>
#include <stdbool.h>
#include <git2.h>
#include <dirent.h>
#include <ustr.h>

/* macros to decrease typing and line length */
#define repo_open_ext git_repository_open_ext
#define repo_discover git_repository_discover

/* If we're in a git repo, returns true and cwd is set to the root .git dir
 * else returns false and *cwd is left untouched.
 */
int gitrepo(Ustr *cwd)
{
     int ret, err;
     char *path = NULL;
     COMNR_DBG("cwd: '%s'\n", cwd);

     /* find the first case of '.git' in cwd */
     if (strstr(cwd, "/.git") == NULL) {
          char *dirs[2] = { cwd, "/.git" };
          path = subdir(dirs, PATH_MAX + 1);
          if (path == NULL) { /* allocation in subdir failed */
               free(path);
               goto rfail;
          }

	  /* check if .git exists in the current directory */
	  if ((ret = direxists(path)) != true && ret == false)
	       path = cwd;

     } else {
	  path = cwd;
     }

     COMNR_DBG("cwd: '%s', path: '%s'\n", cwd, path);
     COMNR_DBG("cwd + path: '%s/%s'\n", cwd, path);
     /* XXX repo_open_ext returns 0 when the git repo has been found */
     ret = repo_open_ext(NULL, path, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
     COMNR_DBG("ret: '%d', GIT_ENOTFOUND: '%d'\n", ret, GIT_ENOTFOUND);
     if (ret == 0)
          goto rok_free;
     /* maybe we're in a subdir of the repository.  Let's check */
     git_buf root;
     memset(&root, 0, sizeof(root));
     err = repo_discover(&root, path, 0, NULL);
     COMNR_DBG("root.asize: '%lu'\n", root.asize);
     /* root.asize is how much memory has been consumed by the path to the repo root */
     if (root.asize > 0) {
          COMNR_DBG("(root dir of git repo) root.ptr: '%s'\n", root.ptr);

          comnr_ping;

          comnr_neko("%s\n", "calling gitrepo recursively");

          gitrepo(root.ptr);
     }
rfail:
     return false;
rok_free:
     free(path);
     return true;
}

gitcommit 

#undef repo_open_ext
#undef repo_discover
