#include "basics.h"

struct tortoise tortoise = {.x = 0.0, .y = 0.0, .direction = 0.0, .pendown = 1};

void draw_line(FILE *output, double x1, double y1, double x2, double y2) {
  fprintf(output, "plot [0:1] %f + %f * t, %f + %f * t notitle\n", x1, x2 - x1,
          y1, y2 - y1);
  fflush(output);
}

void tortoise_reset() {
  tortoise.x = tortoise.y = 0.0;
  tortoise.direction = 0.0;
  tortoise.pendown = 1;

  fprintf(global_output, "clear\n");
  fflush(global_output);
}

int tortoise_pendown() {
  int result = tortoise.pendown;
  tortoise.pendown = 1;
  return result;
}

int tortoise_penup() {
  int result = tortoise.pendown;
  tortoise.pendown = 0;
  return result;
}

double tortoise_turn(double degree) {
  tortoise.direction += M_PI / 180.0 * degree;
  return tortoise.direction * 180.0 / M_PI;
}

struct coord_pair tortoise_move(double length) {
  double newX, newY;

  newX = tortoise.x + length * cos(tortoise.direction);
  newY = tortoise.y + length * sin(tortoise.direction);

  if (tortoise.pendown)
    draw_line(global_output, tortoise.x, tortoise.y, newX, newY);

  tortoise.x = newX;
  tortoise.y = newY;
  struct coord_pair result = {.x = newX, .y = newY};
  return result;
}
