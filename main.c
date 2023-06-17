#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "basics.h"

#include "libguile.h"

static const int WIDTH = 10;
static const int HEIGHT = 10;


static FILE *start_gnuplot() {
  FILE *output;
  int pipes[2];
  pid_t pid;
  if (pipe(pipes)) {
    return NULL;
  }
  pid = fork();
  if (!pid) {
    // we are in child
    dup2(pipes[0], STDIN_FILENO);
    char *const args[] = {"gnuplot", NULL};
    execvp("gnuplot", args);
    /*unreachable*/
    return NULL;
  }
  output = fdopen(pipes[1], "w");

  fprintf(output, "set multiplot\n");
  fprintf(output, "set parametric\n");
  fprintf(output, "set xrange [-%d:%d]\n", WIDTH, WIDTH);
  fprintf(output, "set yrange [-%d:%d]\n", HEIGHT, HEIGHT);
  fprintf(output, "set size ratio -1\n");
  fprintf(output, "unset xtics\n");
  fprintf(output, "unset ytics\n");
  fflush(output);
  return output;
}


static SCM tortoise_reset_guile() {
  tortoise_reset();
  return SCM_UNSPECIFIED;
}

static SCM tortoise_pendown_guile() {
  SCM result = scm_from_bool(tortoise_pendown());
  return result;
}

static SCM tortoise_penup_guile() {
  SCM result = scm_from_bool(tortoise_penup());
  return result;
}

static SCM tortoise_turn_guile(SCM degrees) {
  const double value = scm_to_double(degrees);
  double result = tortoise_turn(value);
  return scm_from_double(result);
}


static SCM tortoise_move_guile(SCM length) {
  const double value = scm_to_double(length);
  struct coord_pair result = tortoise_move(value);
  return scm_list_2(scm_from_double(result.x), scm_from_double(result.y));
}

static void *register_functions(void *data) {
  scm_c_define_gsubr("tortoise-reset", 0, 0, 0, &tortoise_reset_guile);
  scm_c_define_gsubr("tortoise-penup", 0, 0, 0, &tortoise_penup_guile);
  scm_c_define_gsubr("tortoise-pendown", 0, 0, 0, &tortoise_pendown_guile);
  scm_c_define_gsubr("tortoise-turn", 1, 0, 0, &tortoise_turn_guile);
  scm_c_define_gsubr("tortoise-move", 1, 0, 0, &tortoise_move_guile);
  return NULL;
}

int main(int argc, char **argv, char **envp) {
  global_output = start_gnuplot();
  tortoise_reset();
  scm_with_guile(&register_functions, NULL);
  scm_shell(argc, argv);
  return EXIT_SUCCESS;
}
