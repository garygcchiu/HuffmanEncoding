#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libpnm.h"

#ifndef _MEAN_ABSOLUTE_ERROR_
#define _MEAN_ABSOLUTE_ERROR_

float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr);

#endif