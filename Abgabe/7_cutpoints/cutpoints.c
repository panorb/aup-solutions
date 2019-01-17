#include "cp.h"

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct { 
  double x;
  double y;
} vec_t;

typedef struct {
  point_t point_a;
  point_t point_b;
} segment_t;

typedef struct {
  point_t anchor;
  double radius;
} circle_t;

double dot_product(vec_t vec_a, vec_t vec_b) {
  return (vec_a.x * vec_b.x) + (vec_a.y * vec_b.y); 
}

vec_t vec_between(point_t point_a, point_t point_b) {
  vec_t vec;
  vec.x = point_b.x - point_a.x;
  vec.y = point_b.y - point_a.y;
  return vec;
}

vec_t vec_invert(vec_t vec) {
  vec.x = -vec.x;
  vec.y = -vec.y;
  return vec;
}

point_t vec_add(point_t point, vec_t vec) {
  point.x += vec.x;
  point.y += vec.y;
  return point;
}

vec_t direction(segment_t segment) {
  vec_t direction = vec_between(segment.point_a, segment.point_b);
  return direction;
}

circle_t get_circle(point_t point_a, point_t point_b, point_t point_c) {
  // Kreis wird eindeutig durch drei Punkte beschrieben.

}

segment_t segment_between(point_t point_a, point_t point_b) {
    segment_t segment;
    segment.point_a = point_a;
    segment.point_b = point_b;
    return segment;
}

segment_t *get_segments(sprite_t sprite, int *length) {
  segment_t *segments;

  switch (sprite.type) {
    case SHAPE_CIRCLE:
      // Ein Kreis besitzt keine Segmente.
      if (length != NULL) *length = 0;
      segments = NULL;
      printf("Not implemented.");
      break;
    case SHAPE_RECTANGLE:
      // Ein Rechteck besteht aus 4 Segmenten.
      if (length != NULL) *length = 4;
      segments = calloc(4, sizeof(segment_t));

      // TODO: Finde Segment ohne rechten Winkel <- Spiegelachse
      // Restliche Punkte <- Spiegel Punkte

      for (int i = 0; i < 3; i++) { // i = current poin
        int j;
        if (i == 0) j = 2;
        else j = i - 1;

        int k;
        if (i == 2) k = 0;
        else k = i + 1;
        
        printf("i = %d\n", i);
        printf("j (prev) = %d\n", j);
        printf("k (next) = %d\n", k);
        
        segment_t cur_segment = segment_between(sprite.points[i], sprite.points[k]);
        segment_t next_segment = segment_between(sprite.points[k], sprite.points[j]);

        printf("dotproduct = %f\n", dot_product(direction(cur_segment), direction(next_segment)));
        if (dot_product(direction(cur_segment), direction(next_segment)) == 0) { // 
          segments[0] = cur_segment;
          segments[1] = next_segment;

          segments[2].point_a = vec_add(next_segment.point_a, direction(next_segment));
          segments[2].point_b = vec_add(segments[2].point_a, vec_invert(direction(cur_segment)));

          segments[3].point_a = segments[2].point_b;
          segments[3].point_b =  vec_add(segments[3].point_a, vec_invert(direction(next_segment)));

          printf("-- rectangle --\n");
          for (int w = 0; w < 4; w++) {
            printf("segment %d ", w);
            printf(" (%f, %f) ", segments[w].point_a.x, segments[w].point_a.y);
            printf("--- (%f, %f)\n", segments[w].point_b.x, segments[w].point_b.y);
          }
          printf("---------------\n");
          break;
        }
      }
      break;
    case SHAPE_TRIANGLE:
      // Ein Dreieck besteht aus 3 Segmenten.
      if (length != NULL) *length = 3;
      segments = calloc(3, sizeof(segment_t));
      for (int i = 0; i < 3; i++) {
        // int j = i + 1 ? i < 2 : 0;
        int j;
        if (i == 2) j = 0;
        else j = i + 1;

        printf("j = %d\n", j);
        segments[i] = segment_between(sprite.points[i], sprite.points[j]);
      }

      printf("-- triangle --\n");
      for (int w = 0; w < 3; w++) {
        printf("segment %d ", w);
        printf(" (%f, %f) ", segments[w].point_a.x, segments[w].point_a.y);
        printf("--- (%f, %f)\n", segments[w].point_b.x, segments[w].point_b.y);
      }
      printf("---------------\n");
      break;
    default:
      printf("Unerwarteter Fall aufgetreten. sprite.type hat keinen gültigen Wert.");
      return NULL;
  }

  return segments;
}

bool _segment_segment_intersection(segment_t segment_a, segment_t segment_b, point_t *intersect) {
    double s, t;
    s = (-direction(segment_a).y * (segment_a.point_a.x - segment_b.point_a.x) + direction(segment_a).x * (segment_a.point_a.y - segment_b.point_a.y)) / (-direction(segment_b).x * direction(segment_a).y + direction(segment_a).x * direction(segment_b).y);
    t = (direction(segment_b).x * (segment_a.point_a.y - segment_b.point_a.y) - direction(segment_b).y * (segment_a.point_a.x - segment_b.point_a.x)) / (-direction(segment_b).x * direction(segment_a).y + direction(segment_a).x * direction(segment_b).y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (intersect != NULL)
            intersect -> x = segment_a.point_a.x + (t * direction(segment_a).x);
            intersect -> y = segment_a.point_a.y + (t * direction(segment_a).y);
        return true;
    }

    return false; // No collision
}

bool circle_circle_intersection(circle_t circle_a, circle_t circle_b) {

}

bool circle_segment_intersection(circle_t circle, segment_t segment) {
  
}

// Quelle für den Lösungsansatz: https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Intersection_of_two_lines
bool segment_segment_intersection(segment_t segment_a, segment_t segment_b, point_t *intersect) {
  double x1 = segment_a.point_a.x;
  double x2 = segment_a.point_b.x;
  double x3 = segment_b.point_a.x;
  double x4 = segment_b.point_b.x;

  double y1 = segment_a.point_a.y;
  double y2 = segment_a.point_b.y;
  double y3 = segment_b.point_a.y;
  double y4 = segment_b.point_b.y;

  double s, t;
  // if (x2 * y4 == 0 || x4 * y2 == 0) return false; // Division durch 0 verhindern.

  if ((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4) == 0 || ((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)) == 0)
    return false;

  s = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
  t = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));

  printf("s = %f\nt = %f\n", s, t);
  if (0 <= s && s <= 1 && 0 <= t && t <= 1) {
    intersect -> x = x1 + s * direction(segment_a).x;
    intersect -> y = y3 + t * direction(segment_b).y;
    return true;
  }

  return false;
}

point_t *cutpoints(sprite_t sprite_a, sprite_t sprite_b, int *num) {
  int length_a, length_b;
  segment_t* segments_a = get_segments(sprite_a, &length_a);
  segment_t* segments_b = get_segments(sprite_b, &length_b);

  if (length_a == 0 && length_b == 0) {
    // circle - circle intersection
    printf("Not implemented.\n");
    return NULL;
  } else if (length_a > 0 && length_b == 0) {
    // segment - circle intersection
    printf("Not implemented.\n");
    return NULL;
  } else if (length_a == 0 && length_b > 0) {
    // circle - segment intersection
    printf("Not implemented.\n");
    return NULL;
  } else {
    // segment - segment intersection
    point_t intersect;
    for (int i = 0; i < length_a; i++) {
      for (int j = 0; j < length_b; j++) {
        point_t intersect;
        bool has_result = segment_segment_intersection(segments_a[i], segments_b[j], &intersect);
        if (has_result) {
          printf("(%f, %f) ", intersect.x, intersect.y);
        }
      }
    }
  }

  printf("\n");
  return NULL;
}

int main()
{
    // printf("-----------\n");
    // sprite_t sprite_a = {SHAPE_TRIANGLE, {{-1.0, -2.0}, {0.0, 1.0}, {1.0, -2.0}}};
    sprite_t sprite_a = {SHAPE_TRIANGLE, {{-1.0, -2.0}, {0.0, 1.0}, {1.0, -2.0}}};
    // sprite_t sprite_b = {SHAPE_RECTANGLE, {{-1.0, 0.0}, {-1.0, 1.0}, {1.0, 1.0}}};
    sprite_t sprite_b = {SHAPE_RECTANGLE, {{-1.0, 0.0}, {-1.0, -1.0}, {1.0, -1.0}}};

    printf("-----------\n");
    int num;
    cutpoints(sprite_a, sprite_b, &num);
    return 0;
}

