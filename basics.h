#include <math.h>
#include <stdio.h>

FILE *global_output = NULL;

static struct tortoise {
  double x, y;
  double direction;
  int pendown;
} tortoise = {.x = 0.0, .y = 0.0, .direction = 0.0, .pendown = 1};

struct coord_pair {
  double x, y;
};

void draw_line(FILE *output, double x1, double y1, double x2, double y2);

void tortoise_reset();

int tortoise_pendown();

int tortoise_penup();

double tortoise_turn(double degree);

struct coord_pair tortoise_move(double length);
