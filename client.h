#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include <cstring>

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();
    struct pixel;
    struct translateMat;
    struct rotateMat;
    struct scaleMat;
    struct Mat;

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void DDA(float x1, float y1, float x2, float y2, unsigned int color);
    void PageNumber(int page_location);
    void Bresenham(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);
    void PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3);
    void depthCuePolygonRenderer(int x1,int y1,int z1, int x2, int y2, int z2, int x3, int y3, int z3, unsigned int nearColor, unsigned farColor)  ;
    int Distance(int x1, int y1, int x2, int y2);
    bool SimpDrawer(char* filename[]);
};

#endif // CLIENT_H
