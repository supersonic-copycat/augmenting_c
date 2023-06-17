#include <math.h>
#include <stdio.h>

extern FILE *global_output; 

struct tortoise {
  double x, y;
  double direction;
  int pendown;
};

struct coord_pair {
  double x, y;
};

void draw_line(FILE *output, double x1, double y1, double x2, double y2);

void tortoise_reset();

int tortoise_pendown();

int tortoise_penup();

double tortoise_turn(double degree);

struct coord_pair tortoise_move(double length);
