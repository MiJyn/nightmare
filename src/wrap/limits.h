#ifndef _SP_WRAP_LIMITS_H
#define _SP_WRAP_LIMITS_H

#ifdef __linux
#  include <linux/limits.h>
#else
#  define PATH_MAX 4096 // Whatever lol
#endif

#endif
