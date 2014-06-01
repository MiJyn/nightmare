#include "NRsc.h"

#include "NGlobals.h"
#include "NLog.h"

#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "wrap/limits.h"
#include <string.h>
#include "NDynamic_t.h"
#include <dirent.h>

#ifdef WIN32
#  include <windows.h>
#endif

bool NRsc_init() {
    char exepath[PATH_MAX + 1];
#ifdef WIN32
    GetModuleFileName(GetModuleHandle(NULL), exepath, PATH_MAX);
#else
    char* result = realpath("/proc/self/exe", exepath);
    if (!result) {
        Nerror("Can't figure out self path!");
        return false;
    }
#endif
    char* toppath = dirname(dirname(exepath));
    N_rsc_path = malloc(strlen(toppath) + 7);
    strcpy(N_rsc_path, toppath);
    strcat(N_rsc_path, N_SLASH "game");
    Ndebug(N_rsc_path);
    return true;
}

void NRsc_destroy() {
    free(N_rsc_path);
}

// FREE
char* NRsc_join_paths(char* path1, char* path2) {
    char* newpath = malloc(strlen(path1) + strlen(path2) + 2);
    strcpy(newpath, path1);
    strcat(newpath, N_SLASH);
    strcat(newpath, path2);
    return newpath;
}

// FREE
char* NRsc_remove_ext(char* path) {
    char* dot = strrchr(path, '.');
    size_t dot_pos;
    if (dot == NULL) {
        dot_pos = strlen(path);
    } else {
        dot_pos = dot - path;
    }
    char* ret = malloc(dot_pos + 1);
    strncpy(ret, path, dot_pos);
    ret[dot_pos] = 0;
    return ret;
}

// FREE
char* NRsc_get_path(char* simplepath) {
    char* newpath = malloc(strlen(N_rsc_path) + strlen(simplepath) + 2);
    strcpy(newpath, N_rsc_path);
    strcat(newpath, N_SLASH);
    strcat(newpath, simplepath);
    return newpath;
}

char** NRsc_ls(char* simplepath) {
    NLIST_NEW(char*, ret);

    char* path = NRsc_get_path(simplepath);
    DIR* dir = opendir(path);
    free(path);

    struct dirent* entry;
    char* curname;
    while ((entry = readdir(dir)) != NULL) {
        // Checks if it's "." or ".."
        if (entry->d_name[0] == '.' && (entry->d_name[1] == 0 || (entry->d_name[1] == '.' && entry->d_name[2] == 0))) {
            continue;
        }
        curname = malloc(strlen(entry->d_name) + 1);
        strcpy(curname, entry->d_name);
        NLIST_PUSH(ret, curname);
    }
    closedir(dir);
    return ret.data;
}

#if 0
// One liner, because boredom XD
// Warns about ignoring the value of realloc (harmless), so that's why I'm using the longer version instead
void NRsc_ls_free(char**a){for(long j,i=0;!(((!(j=(long)a[i]))||(((long)realloc((char*)j,0))&0))&&(!(((long)realloc(a,0))&0)));i++);}
#else
void NRsc_ls_free(char** lsd) {
    char* file;
    for (int i = 0; (file = lsd[i]); i++) {
        free(file);
    }
    free(lsd);
}
#endif

char* NRsc_read_file(char* simplepath) {
    char* path = NRsc_get_path(simplepath);
    FILE* file = fopen(path, "r");
    free(path);
    if (file == NULL) {
        Nerror("Error loading file!");
        return NULL;
    }

    fseek (file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind (file);

    char* ret = malloc(file_size + 1);
    memset(ret, 0, file_size + 1);
    size_t n_read = fread(ret, 1, file_size, file);
    if (n_read != file_size) {
        Nerror("Error reading file!");
        return NULL;
    }
    //ret[file_size] = 0;
    Ndebug(ret);
    fclose(file);
    //ret = realloc(ret, strlen(ret)); // Save memory
    return ret;
}