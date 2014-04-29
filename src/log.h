#ifndef _SP_LOG_H
#define _SP_LOG_H

#include "compat.h"

#include "globals.h"

START_HEAD

int info(const char* fmt, ...);
int debug(const char* fmt, ...);
int error(const char* fmt, ...);
void newline();

#define indent(type, func) \
type##_indent++;\
func;\
type##_indent--

END_HEAD

#endif