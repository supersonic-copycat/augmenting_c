#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libguile.h"

static FILE *global_output = NULL;
static const int WIDTH = 10;
static const int HEIGHT = 10;

static double x, y;
static double direction;
static int pendown;

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
    execlp("gnuplot", (char *)NULL);
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
static void draw_line(FILE *output, double x1, double y1, double x2,
                      double y2) {
  fprintf(output, "plot [0:1] %f + %f * t, %f + %f * t notitle\n", x1, x2 - x1,
          y1, y2 - y1);
  fflush(output);
}

static void tortoise_reset() {
  x = y = 0.0;
  direction = 0.0;
  pendown = 1;

  fprintf(global_output, "clear\n");
  fflush(global_output);
}

static void tortoise_pendown() { pendown = 1; }

static void tortoise_penup() { pendown = 0; }

static void tortoise_turn(double degrees) {
  direction += M_PI / 180.0 * degrees;
}

static void tortoise_move(double length) {
  double newX, newY;

  newX = x + length * cos(direction);
  newY = y + length * sin(direction);

  if (pendown)
    draw_line(global_output, x, y, newX, newY);

  x = newX;
  y = newY;
}

int main(int argc, char **argv, char **envp) {
  global_output = start_gnuplot();
  tortoise_reset();
  {
    int i;
    tortoise_pendown(); /* This is unnecessary, but makes it clearer.  */
    for (i = 1; i <= 4; ++i) {
      tortoise_move(3.0);
      tortoise_turn(90.0);
    }
  }
  return EXIT_SUCCESS;
}
