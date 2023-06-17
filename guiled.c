#include "guiled.h"

SCM tortoise_reset_guile() {
  tortoise_reset();
  return SCM_UNSPECIFIED;
}

SCM tortoise_pendown_guile() {
  SCM result = scm_from_bool(tortoise_pendown());
  return result;
}

SCM tortoise_penup_guile() {
  SCM result = scm_from_bool(tortoise_penup());
  return result;
}

SCM tortoise_turn_guile(SCM degrees) {
  const double value = scm_to_double(degrees);
  double result = tortoise_turn(value);
  return scm_from_double(result);
}

SCM tortoise_move_guile(SCM length) {
  const double value = scm_to_double(length);
  struct coord_pair result = tortoise_move(value);
  return scm_list_2(scm_from_double(result.x), scm_from_double(result.y));
}

void *register_functions(void *data) {
  scm_c_define_gsubr("tortoise-reset", 0, 0, 0, &tortoise_reset_guile);
  scm_c_define_gsubr("tortoise-penup", 0, 0, 0, &tortoise_penup_guile);
  scm_c_define_gsubr("tortoise-pendown", 0, 0, 0, &tortoise_pendown_guile);
  scm_c_define_gsubr("tortoise-turn", 1, 0, 0, &tortoise_turn_guile);
  scm_c_define_gsubr("tortoise-move", 1, 0, 0, &tortoise_move_guile);
  return NULL;
}
