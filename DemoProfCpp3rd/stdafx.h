// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define FUNC_INFO (printf("-------------------- Function %s --------------------\n", __func__));
#define SUBFUNC_INFO (printf("---------- Sub-Function %s ----------\n", __func__));
#define PASS_INFO(k) (printf("---------- Pass %u ----------\n", k));

// TODO: reference additional headers your program requires here
