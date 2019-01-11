#include "cp.h"

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct { 
  double x;
  double y;
} vec_t;

typedef struct {
    point_t anchor;
    vec_t direction;
} segment_t;

point_t *cutpoints(sprite_t sprite_a, sprite_t sprite_b, int *num) {

}

segment_t *get_segments(sprite_t sprite) {
  segment_t *segments;

  switch (sprite.type) {
    case SHAPE_CIRCLE:
      // Ein Kreis besitzt keine Segmente.
      segments = NULL;
      break;
    case SHAPE_RECTANGLE:
      // Ein Rechteck besteht aus 4 Segmenten.
      segments = calloc(4, sizeof(segment_t));

      // TODO: Finde Segment ohne rechten Winkel <- Spiegelachse
      // Restliche Punkte <- Spiegel Punkte
      break;
    case SHAPE_TRIANGLE:
      // Ein Dreieck besteht aus 3 Segmenten.
      segments = calloc(3, sizeof(segment_t));
      for (int i = 0; i < 3; i++) {
        int j = i + 1 ? i < 2 : 0;
        segments[i] = segment_between(sprite.points[i], sprite.points[j]);
      }
      break;
    default:
      printf("Unerwarteter Fall aufgetreten. sprite.type hat keinen gültigen Wert.");
      return NULL;
  }

  return segments;
}

segment_t segment_between(point_t point_a, point_t point_b) {
    vec_t vec;
    vec.x = point_b.x - point_a.x;
    vec.y = point_b.y - point_a.x;

    segment_t segment;
    segment.anchor = point_a;
    segment.direction = vec;
    return segment;
}