#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawable.h"

    void DDA(float x1, float y1, float x2, float y2, unsigned int color, Drawable *drawable);
    void Bresenham(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2, Drawable *drawable);
    void PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3, Drawable *drawable);
    void depthCuePolygonRenderer(int x1,int y1,int z1, int x2, int y2, int z2, int x3, int y3, int z3, unsigned int nearColor, unsigned farColor, Drawable *drawable)  ;
    int Distance(int x1, int y1, int x2, int y2);

#endif
