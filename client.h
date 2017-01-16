#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include "LineDrawer.h"
#include <cstring>

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();
    struct pixel;
    struct meshPixel;
    struct Mat;

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void PageNumber(int page_location);
    bool SimpDrawer(char* filename[], unsigned int nearColour, unsigned int farColour);
    bool meshRenderer(const char* filename, Mat m, unsigned int nearColour, unsigned int farColour);
};

#endif // CLIENT_H
