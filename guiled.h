#ifndef _TORTOISE_TUTORIAL_GUILE_H
#define _TORTOISE_TUTORIAL_GUILE_H
#include "basics.h"
#include "libguile.h"

SCM tortoise_reset_guile();

SCM tortoise_pendown_guile();

SCM tortoise_penup_guile();

SCM tortoise_turn_guile(SCM degrees);

SCM tortoise_move_guile(SCM length);

void *register_functions(void *data);

#endif // _TORTOISE_TUTORIAL_GUILE_H
