#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();
    struct pixel;

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void DDA(float x1, float y1, float x2, float y2, unsigned int color);
    void PageNumber(int page_location);
    void Bresenham(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);
    void PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3);
    int Distance(int x1, int y1, int x2, int y2);
};

#endif // CLIENT_H
