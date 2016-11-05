#include <iostream>
#include <math.h>
#include <QTextStream>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream> //parse simp file
using std::ifstream;
#include <string>
#include <stack>
#include "client.h"

# define PI  3.14159265358979323846  /* pi */

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS = 500;
const char* const DELIMITER = "\"    \t,()\n";

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}

struct Client::pixel{
    int x;
    int y;
};

struct Client::meshPixel{
    int x;
    int y;
    int z;
};
typedef struct meshPixel meshPixel;

struct Client::Mat{
    float mat[4][4];
    Mat(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i==j) mat[i][j]=1.0;
                else mat[i][j]=0.0;
            }
        }
    }
};
typedef struct Mat Mat;


void Client::nextPage() {
    static int pageNumber = 0;
    pageNumber++;
    //std::cout << "PageNumber " << pageNumber << std::endl;

    switch(pageNumber % 9) {
    case 1:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();   // you must call this to make the display change.
        PageNumber(1);
        break;
    case 2:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(2);
        break;
    case 3:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(3);
        break;
    case 4:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(4);
        break;
    case 5:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(5);
        break;
    case 6:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(6);
        break;
    case 7:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(7);
        break;
    case 8:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        PageNumber(8);
        break;

    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
    }
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}


// Digital Differential Analyzer Algorithm
// Check if the slope value is between -1 and 1
// If so increment/decrement y along x++ or x--
// Otherwise if slope is not between -1 and 1
// Increment/decrement x along y++ or y--
void Client::DDA(float x1, float y1, float x2, float y2, unsigned int color){
    float dx = x2-x1;
    float dy = y2-y1;
    float m = (float)dy/(float)dx;
    float b = y1-m*x1;
    float y;
    // check slope to see which octant
    if(abs(m)>=0 && abs(m)<1)
    {
        int i = 0;
        if(dx>0){
            for(float x = x1; x<x2; x++){
                    y = m*x + b;
                    drawable->setPixel(x,y,color);
                    i++;
                }

        }
        else{
            for(float x = x1; x>x2; x--){
                    y = m*x + b;
                    drawable->setPixel(x,y,color);
                    i++;
                }
        }

    }
    else{
        if(dy>0){
            float x;
            for(float y=y1; y<y2; y++){
                x = (y-b)/m;

                drawable->setPixel(x,y,color);
            }
        }
        else{
            float x;
            for(float y=y1; y>y2; y--){
                x = (y-b)/m;

                drawable->setPixel(x,y,color);
            }
        }
    }
}

// Bresenham's algorithm
// 8 octants are set up by 3 conditional statements
// first compare dx and dy,
// then y2 and y1 or x2 and x1,
// then x2 and x1 or y2 and y1
void Client::Bresenham(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2){
    int dx = x2-x1;
    if(x1>x2) {
        dx = x1-x2;
    }

    int dy = y2-y1;
    if(y1>y2) {
        dy = y1-y2;
    }

    int two_dx = 2*dx;
    int two_dy = 2*dy;

    int r1,g1,b1,r2,b2,g2,rounded_r,rounded_g,rounded_b;

    r1 = (color1>>16)& 0xff;
    g1 = (color1>>8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2>>16)& 0xff;
    g2 = (color2>>8) & 0xff;
    b2 = color2 & 0xff;


    unsigned int current_Color;

    drawable->setPixel(x1,y1,color1);

    if(dx>dy){
        int err = two_dy-dx;
        int t2 = two_dy-two_dx;



        if(y2>y1){
            int y = y1;
            if(x2>x1){
                int ddx = x2 - x1;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                // Traverse along x+
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y++;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddx = x1 - x2;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                // Traverse along x-
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y++;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
        else{
            if(x2>x1){
                int ddx = x2 - x1;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                int y = y1;
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y--;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddx = x1 - x2;
                float dr = r2-r1;
                dr = dr/ddx;
                float dg = g2-g1;
                dg = dg/ddx;
                float db = b2-b1;
                db = db/ddx;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;
                int y = y1;
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y--;
                    }
                    else{
                        err = err+two_dy;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);
                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
    }
    else{
        int err = two_dx-dy;
        int t2 = two_dx-two_dy;
        if(x2>x1){
                if(y2>y1){
                    int ddy = y2 - y1;
                    float dr = r2-r1;
                    dr = dr/ddy;
                    float dg = g2-g1;
                    dg = dg/ddy;
                    float db = b2-b1;
                    db = db/ddy;

                    float temp_r = r1;
                    float temp_g = g1;
                    float temp_b = b1;

                    int x = x1;
                    // Traverse along y+
                    for(int y=y1+1; y<=y2; y++){
                        if (err>=0){
                            err = err + t2;
                            x++;
                        }
                        else{
                            err = err+two_dx;
                        }
                        temp_r = temp_r+dr;
                        temp_g = temp_g+dg;
                        temp_b = temp_b+db;
                        rounded_r = round(temp_r);
                        rounded_g = round(temp_g);
                        rounded_b = round(temp_b);

                        current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                        drawable->setPixel(x,y,current_Color);
                    }
                }
                else{
                    int ddy = y1 - y2;
                    float dr = r2-r1;
                    dr = dr/ddy;
                    float dg = g2-g1;
                    dg = dg/ddy;
                    float db = b2-b1;
                    db = db/ddy;

                    float temp_r = r1;
                    float temp_g = g1;
                    float temp_b = b1;

                    int x = x1;
                    for(int y=y1+1; y>=y2; y--){
                        if (err>=0){
                            err = err + t2;
                            x++;
                        }
                        else{
                            err = err+two_dx;
                        }
                        temp_r = temp_r+dr;
                        temp_g = temp_g+dg;
                        temp_b = temp_b+db;
                        rounded_r = round(temp_r);
                        rounded_g = round(temp_g);
                        rounded_b = round(temp_b);

                        current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                        drawable->setPixel(x,y,current_Color);
                    }
                }
        }
        else{
            if(y2>y1){
                int ddy = y2 - y1;
                float dr = r2-r1;
                dr = dr/ddy;
                float dg = g2-g1;
                dg = dg/ddy;
                float db = b2-b1;
                db = db/ddy;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;

                int x = x1;
                // Traverse along y+
                for(int y=y1+1; y<=y2; y++){
                    if (err>=0){
                        err = err + t2;
                        x--;
                    }
                    else{
                        err = err+two_dx;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;
                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                int ddy = y1 - y2;
                float dr = r2-r1;
                dr = dr/ddy;
                float dg = g2-g1;
                dg = dg/ddy;
                float db = b2-b1;
                db = db/ddy;

                float temp_r = r1;
                float temp_g = g1;
                float temp_b = b1;

                int x = x1;
                // Traverse along y-
                for(int y=y1+1; y>=y2; y--){
                    if (err>=0){
                        err = err + t2;
                        x--;
                    }
                    else{
                        err = err+two_dx;
                    }
                    temp_r = temp_r+dr;
                    temp_g = temp_g+dg;
                    temp_b = temp_b+db;

                    rounded_r = round(temp_r);
                    rounded_g = round(temp_g);
                    rounded_b = round(temp_b);

                    current_Color = (0xff<<24) + ((rounded_r & 0xff)<<16) + ((rounded_g & 0xff)<<8) + (rounded_b & 0xff);

                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
    }
}



void Client::PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3){
    // initialize edge case for vertical lines
    bool VertLine_p1p2 = false;
    bool VertLine_p1p3 = false;
    bool VertLine_p2p3 = false;
    float x1,y1,x2,y2,x3,y3;
    int r1,g1,b1,r2,b2,g2,r3,g3,b3,long_rounded_r,long_rounded_g,long_rounded_b,a_rounded_r,a_rounded_g,a_rounded_b,b_rounded_r,b_rounded_g,b_rounded_b;

    // Assigning parameters to p1,p2,p3
    // (x1,y1)->(x2,y2) is assigned to be the longest line
    if(Distance(xx1,yy1,xx2,yy2)>=Distance(xx1,yy1,xx3,yy3) && Distance(xx1,yy1,xx2,yy2)>=Distance(xx2,yy2,xx3,yy3)){
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        x3 = xx3;
        y3 = yy3;

        r1 = (color1>>16)& 0xff;
        g1 = (color1>>8) & 0xff;
        b1 = color1 & 0xff;
        r2 = (color2>>16)& 0xff;
        g2 = (color2>>8) & 0xff;
        b2 = color2 & 0xff;
        r3 = (color3>>16)& 0xff;
        g3 = (color3>>8) & 0xff;
        b3 = color3 & 0xff;

        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

    }
    else if(Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx2,yy2) && Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx3,yy3)){
        x1 = xx2;
        y1 = yy2;
        x2 = xx3;
        y2 = yy3;
        x3 = xx1;
        y3 = yy1;

        r1 = (color2>>16)& 0xff;
        g1 = (color2>>8) & 0xff;
        b1 = color2 & 0xff;
        r2 = (color3>>16)& 0xff;
        g2 = (color3>>8) & 0xff;
        b2 = color3 & 0xff;
        r3 = (color1>>16)& 0xff;
        g3 = (color1>>8) & 0xff;
        b3 = color1 & 0xff;

        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;


    }
    else{
        x1 = xx1;
        y1 = yy1;
        x2 = xx3;
        y2 = yy3;
        x3 = xx2;
        y3 = yy2;

        r1 = (color1>>16)& 0xff;
        g1 = (color1>>8) & 0xff;
        b1 = color1 & 0xff;
        r2 = (color3>>16)& 0xff;
        g2 = (color3>>8) & 0xff;
        b2 = color3 & 0xff;
        r3 = (color2>>16)& 0xff;
        g3 = (color2>>8) & 0xff;
        b3 = color2 & 0xff;
        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;
    }

    QTextStream(stdout)<<"(x,y)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;



    // Declaration for the longest line p1p2
    float long_dx = x2-x1;
    float long_dy = y2-y1;
    float long_m = (float)long_dy/(float)long_dx;
    float long_b = y1-long_m*x1;
    float long_y;
    float long_x;

    // Declaration for line p1p3
    float a_dx = x3-x1;
    float a_dy = y3-y1;
    float a_m = (float)a_dy/(float)a_dx;
    float a_b = y1-a_m*x1;
    float a_x;
    float a_y;

    // Declaration for line p2p3
    float b_dx = x3-x2;
    float b_dy = y3-y2;
    float b_m = (float)b_dy/(float)b_dx;
    float b_b = y2-b_m*x2;
    float b_x;
    float b_y;

    float temp_long_r = r1;
    float temp_long_g = g1;
    float temp_long_b = b1;
    float temp_a_r = r1;
    float temp_a_g = g1;
    float temp_a_b = b1;
    float temp_b_r = r3;
    float temp_b_g = g3;
    float temp_b_b = b3;

    QTextStream(stdout)<<"r1= "<<r1<<" g1= "<<g1<<" b1= "<<b1<<endl;
    QTextStream(stdout)<<"r2= "<<r2<<" g2= "<<g2<<" b2= "<<b2<<endl;
    QTextStream(stdout)<<"r3= "<<r3<<" g3= "<<g3<<" b3= "<<b3<<endl;

    unsigned int current_Color1, current_Color2, current_Color3;

    drawable->setPixel(x1,y1,color1);



    //Check for vertical slope (m = infinity)
    if((x1-x2)==0){
        VertLine_p1p2 = true;
        QTextStream(stdout)<<"p1p2 inf slope"<<endl;
    }
    if((x1-x3)==0){
        VertLine_p1p3 = true;
        QTextStream(stdout)<<"p1p3 inf slope"<<endl;
    }
    if((x2-x3)==0){
        VertLine_p2p3 = true;
        QTextStream(stdout)<<"p2p3 inf slope"<<endl;
    }

    if(abs(long_m)<1){
        int long_ddx = abs(x2 - x1);
        float long_dr = r2-r1;
        long_dr = long_dr/long_ddx;
        float long_dg = g2-g1;
        long_dg = long_dg/long_ddx;
        float long_db = b2-b1;
        long_db = long_db/long_ddx;

        int a_ddx = abs(x3 - x1);
        float a_dr = r3-r1;
        a_dr = a_dr/a_ddx;
        float a_dg = g3-g1;
        a_dg = a_dg/a_ddx;
        float a_db = b3-b1;
        a_db = a_db/a_ddx;

        int b_ddx = abs(x2 - x3);
        float b_dr = r2-r3;
        b_dr = b_dr/b_ddx;
        float b_dg = g2-g3;
        b_dg = b_dg/b_ddx;
        float b_db = b2-b3;
        b_db = b_db/b_ddx;

        if(long_dx>0){// x1<x2
            QTextStream(stdout)<<"1"<<endl;
            for(float x = x1+1;x<=x2;x++){
                long_y=long_m*x+long_b;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(x<=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    Bresenham(x,long_y,x,a_y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);
                    Bresenham(x,long_y,x,b_y,current_Color1,current_Color3);
                }

            }
        }
        else{
            QTextStream(stdout)<<"2"<<endl;
            for(float x=x1-1;x>=x2;x--){
                long_y=long_m*x+long_b;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(x>=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }
                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    Bresenham(x,long_y,x,a_y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }
                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    Bresenham(x,long_y,x,b_y,current_Color1,current_Color3);
                }
            }
        }
    }
    else{
        int long_ddy = abs(y2 - y1);
        float long_dr = r2-r1;
        long_dr = long_dr/long_ddy;
        float long_dg = g2-g1;
        long_dg = long_dg/long_ddy;
        float long_db = b2-b1;
        long_db = long_db/long_ddy;

        int a_ddy = abs(y3 - y1);
        float a_dr = r3-r1;
        a_dr = a_dr/a_ddy;
        float a_dg = g3-g1;
        a_dg = a_dg/a_ddy;
        float a_db = b3-b1;
        a_db = a_db/a_ddy;

        int b_ddy = abs(y2 - y3);
        float b_dr = r2-r3;
        b_dr = b_dr/b_ddy;
        float b_dg = g2-g3;
        b_dg = b_dg/b_ddy;
        float b_db = b2-b3;
        b_db = b_db/b_ddy;

        if(long_dy>0){
            QTextStream(stdout)<<"3"<<endl;
            for(float y=y1+1;y<=y2;y++){
                if(VertLine_p1p2){
                    long_x=x1;
                }
                else long_x=(y-long_b)/long_m;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(y<=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    Bresenham(long_x,y,a_x,y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    Bresenham(long_x,y,b_x,y,current_Color1,current_Color3);
                }
            }
        }
        else{
            QTextStream(stdout)<<"4"<<endl;
            for(float y=y1-1; y>=y2; y--){
                if(VertLine_p1p2){
                    long_x=x1;
                }
                else long_x=(y-long_b)/long_m;

                temp_long_r = temp_long_r+long_dr;
                temp_long_g = temp_long_g+long_dg;
                temp_long_b = temp_long_b+long_db;
                long_rounded_r = round(temp_long_r);
                long_rounded_g = round(temp_long_g);
                long_rounded_b = round(temp_long_b);

                current_Color1 = (0xff<<24) + ((long_rounded_r & 0xff)<<16) + ((long_rounded_g & 0xff)<<8) + (long_rounded_b & 0xff);

                if(y>=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }

                    temp_a_r = temp_a_r+a_dr;
                    temp_a_g = temp_a_g+a_dg;
                    temp_a_b = temp_a_b+a_db;
                    a_rounded_r = round(temp_a_r);
                    a_rounded_g = round(temp_a_g);
                    a_rounded_b = round(temp_a_b);

                    current_Color2 = (0xff<<24) + ((a_rounded_r & 0xff)<<16) + ((a_rounded_g & 0xff)<<8) + (a_rounded_b & 0xff);

                    Bresenham(long_x,y,a_x,y,current_Color1,current_Color2);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }

                    temp_b_r = temp_b_r+b_dr;
                    temp_b_g = temp_b_g+b_dg;
                    temp_b_b = temp_b_b+b_db;
                    b_rounded_r = round(temp_b_r);
                    b_rounded_g = round(temp_b_g);
                    b_rounded_b = round(temp_b_b);

                    current_Color3 = (0xff<<24) + ((b_rounded_r & 0xff)<<16) + ((b_rounded_g & 0xff)<<8) + (b_rounded_b & 0xff);

                    Bresenham(long_x,y,b_x,y,current_Color1,current_Color3);
                }
            }
        }
    }

}

void Client::depthCuePolygonRenderer(int x1,int y1,int z1, int x2, int y2, int z2, int x3, int y3, int z3, unsigned int nearColor, unsigned farColor){
    // define zNear and zFar clipping planes
    if(z1<=200 && z1>=0 && z2<=200 && z2>=0 && z3<=200 && z3>=0){
        float rNear = (nearColor>>16)& 0xff;
        float gNear = (nearColor>>8) & 0xff;
        float bNear = nearColor & 0xff;
        float rFar = (farColor>>16)& 0xff;
        float gFar = (farColor>>8) & 0xff;
        float bFar = farColor & 0xff;

        float dr = rFar-rNear;
        dr = dr/200;
        float dg = gFar-gNear;
        dg = dg/200;
        float db = bFar - bNear;
        db = db/200;

        float z1_percentage = z1/2;
        z1_percentage = z1_percentage/100;
        z1_percentage = 1 - z1_percentage;
        float z2_percentage = z2/2;
        z2_percentage = z2_percentage/100;
        z2_percentage = 1 - z2_percentage;
        float z3_percentage = z3/2;
        z3_percentage = z3_percentage/100;
        z3_percentage = 1 - z3_percentage;

        int r1 = round(rNear*z1_percentage);
        int g1 = round(gNear*z1_percentage);
        int b1 = round(bNear*z1_percentage);
        int r2 = round(rNear*z2_percentage);
        int g2 = round(gNear*z2_percentage);
        int b2 = round(bNear*z2_percentage);
        int r3 = round(rNear*z3_percentage);
        int g3 = round(gNear*z3_percentage);
        int b3 = round(bNear*z3_percentage);

        unsigned int current_Color1 = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
        unsigned int current_Color2 = (0xff<<24) + ((r2 & 0xff)<<16) + ((g2 & 0xff)<<8) + (b2 & 0xff);
        unsigned int current_Color3 = (0xff<<24) + ((r3 & 0xff)<<16) + ((g3 & 0xff)<<8) + (b3 & 0xff);

        PolygonRenderer(x1,y1,x2,y2,x3,y3,current_Color1,current_Color2,current_Color3);
    }
}


void Client::PageNumber(int page_location){
    ///////////////////////
    // Page 1: Wireframe //
    ///////////////////////
    if(page_location==1){
        qsrand(time(NULL)); // random seeding
        struct pixel gird_point[10][10];
        int shift_x;
        int shift_y;
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                gird_point[i][j].x = 100+60*j;
                gird_point[i][j].y = 100+60*i;

                shift_x = qrand() % 20;
                shift_y = qrand() % 20;
                gird_point[i][j].x += shift_x;
                gird_point[i][j].y += shift_y;
                drawable->setPixel(gird_point[i][j].x,gird_point[i][j].y,0xffffffff);
            }
        }
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                int r1 = qrand() % 256;
                int g1 = qrand() % 256;
                int b1 = qrand() % 256;
                int r2 = qrand() % 256;
                int g2 = qrand() % 256;
                int b2 = qrand() % 256;
                unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);
                unsigned int colour2 = (0xff<<24)+((r2&0xff)<<16)+((g2&0xff)<<8)+(b2&0xff);

                if(j<9){
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i][j+1].x,gird_point[i][j+1].y,colour1,colour2);
                }
                if(i<9){
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i+1][j].x,gird_point[i+1][j].y,colour1,colour2);
                }
                if(i!=0 && i<=9 && j<9){
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i-1][j+1].x,gird_point[i-1][j+1].y,colour1,colour2);
                }
            }
        }
    }
    //////////////////
    // Page 2: Mesh //
    //////////////////
    else if(page_location==2){
        qsrand(time(NULL)); // random seeding
        struct pixel gird_point[10][10];
        int shift_x;
        int shift_y;
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                gird_point[i][j].x = 100+60*j;
                gird_point[i][j].y = 100+60*i;

                shift_x = qrand() % 20;
                shift_y = qrand() % 20;
                gird_point[i][j].x += shift_x;
                gird_point[i][j].y += shift_y;
                QTextStream(stdout)<<"(x1,y1)=("<<gird_point[i][j].x<<",";
                QTextStream(stdout)<<gird_point[i][j].y<<")  ";
            }
        }
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                int r1 = qrand() % 256;
                int g1 = qrand() % 256;
                int b1 = qrand() % 256;
                int r2 = qrand() % 256;
                int g2 = qrand() % 256;
                int b2 = qrand() % 256;
                int r3 = qrand() % 256;
                int g3 = qrand() % 256;
                int b3 = qrand() % 256;
                unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);
                unsigned int colour2 = (0xff<<24)+((r2&0xff)<<16)+((g2&0xff)<<8)+(b2&0xff);
                unsigned int colour3 = (0xff<<24)+((r3&0xff)<<16)+((g3&0xff)<<8)+(b3&0xff);

                if(j<9 && i<9){
                    PolygonRenderer(gird_point[i][j].x,gird_point[i][j].y,gird_point[i][j+1].x,gird_point[i][j+1].y,gird_point[i+1][j].x,gird_point[i+1][j].y,colour1,colour2,colour3);
                    PolygonRenderer(gird_point[i+1][j].x,gird_point[i+1][j].y,gird_point[i+1][j+1].x,gird_point[i+1][j+1].y,gird_point[i][j+1].x,gird_point[i][j+1].y,colour3,colour1,colour2);
                }
            }
        }
    }
    else if(page_location==3){

        char* filename[] = {"page3.txt"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==4){

        char* filename[] = {"page4.txt"};
        SimpDrawer(filename, 0xff00CC66, 0xff008040);
    }
    else if(page_location==5){
        char* filename[] = {"page5.txt"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==6){
        char* filename[] = {"test1.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==7){
        char* filename[] = {"test2.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==8){
        char* filename[] = {"test3.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
}

int Client::Distance(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}






bool Client::SimpDrawer(char* filename[], unsigned int nearColour, unsigned int farColour){
    ifstream fin;

    fin.open(*filename);// open simp file
    if(fin.fail()){// check if open successfully
        QTextStream(stdout) << "file open error.."<<endl;
        return false;
    }

    const char* tempTok[MAX_TOKENS][MAX_TOKENS] = {}; // initialize to 0
    int lineCount=0;
    const char* token[MAX_TOKENS][MAX_TOKENS] = {};

    while(!fin.eof()){
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];

        fin.getline(buf, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index

        tempTok[lineCount][n] = strtok(buf, DELIMITER); // first token

        if (tempTok[lineCount][0]) // zero if line is blank
        {
          for (n = 1; n < MAX_TOKENS; n++)
          {
            tempTok[lineCount][n] = strtok(NULL, DELIMITER); // subsequent tokens
            if (!tempTok[lineCount][n]) break; // no more tokens
          }
        }

        int i =0;
        // process (print) the tokens
        for (i; i < n; i++){
          token[lineCount][i] = strdup(tempTok[lineCount][i]);
        }
        token[lineCount][i] = "~";
        lineCount++;
    }



    fin.close();


    ////////////////////////////////////////
    // text file is tokenized             //
    // now use the array to output screen //
    ////////////////////////////////////////

    // Define initial Coordinate system
    std::stack<Mat>mstack;
    Mat m;
    mstack.push(m);
    Mat world_m;
    world_m.mat[0][0]=3.25;
    world_m.mat[1][1]=3.25;
    world_m.mat[0][3]=325;
    world_m.mat[1][3]=325;

    bool fill = true;

    int x1,x2,x3,y1,y2,y3,z1,z2,z3;// temp variables for assigning polygon


    for(int j=0;j<lineCount;j++){

        int i = 0; //command iteration
        while(strcmp(token[j][i],"~")!=0){
            if(strcmp(token[j][i],"#")==0){} // do nothing if the line is a comment
            /////////////////
            // CTM Section //
            /////////////////
            // want to only do one push per scope, so need to iterate through
            else if((strcmp(token[j][i],"{"))==0){
                Mat prev_m = mstack.top();
                Mat m;
                int k=j+1;
                while((strcmp(token[k][i],"translate"))==0 || (strcmp(token[k][i],"scale"))==0 || (strcmp(token[k][i],"rotate"))==0){
                    if((strcmp(token[k][i],"translate"))==0){
                        m.mat[0][3]=m.mat[0][3]+atof(token[k][i+1]);
                        m.mat[1][3]=m.mat[1][3]+atof(token[k][i+2]);
                        m.mat[2][3]=m.mat[2][3]+atof(token[k][i+3]);
                        k++;
                    }
                    else if((strcmp(token[k][i],"scale"))==0){
                        Mat tempm;
                        Mat tempResult;
                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    tempResult.mat[ii][jj]=0;
                                }
                        }
                        tempm.mat[0][0]=atof(token[k][i+1]);
                        tempm.mat[1][1]=atof(token[k][i+2]);
                        tempm.mat[2][2]=atof(token[k][i+3]);

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    for(int kk=0;kk<4;kk++){
                                        tempResult.mat[ii][jj]+= m.mat[ii][kk]*tempm.mat[kk][jj];
                                    }
                                }
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    m.mat[ii][jj]=tempResult.mat[ii][jj];
                                }
                        }
                        k++;

                    }
                    else if((strcmp("rotate",token[k][i]))==0){
                        Mat tempm;
                        Mat tempResult;
                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    tempResult.mat[ii][jj]=0;
                                }
                        }

                        if ((strcmp(token[k][i+1],"X"))==0){
                            tempm.mat[1][1]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][2]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][1]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][2]=cos(atof(token[k][i+2])*PI/180);
                        }
                        else if((strcmp(token[k][i+1],"Y"))==0){
                            tempm.mat[0][0]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[0][2]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][0]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[2][2]=cos(atof(token[k][i+2])*PI/180);
                        }
                        else if((strcmp(token[k][i+1],"Z"))==0){
                            tempm.mat[0][0]=cos(atof(token[k][i+2])*PI/180);
                            tempm.mat[0][1]=-sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][0]=sin(atof(token[k][i+2])*PI/180);
                            tempm.mat[1][1]=cos(atof(token[k][i+2])*PI/180);
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    for(int kk=0;kk<4;kk++){
                                        tempResult.mat[ii][jj]+= m.mat[ii][kk]*tempm.mat[kk][jj];
                                    }
                                }
                        }

                        for(int ii=0;ii<4;ii++){
                                for(int jj=0;jj<4;jj++){
                                    m.mat[ii][jj]=tempResult.mat[ii][jj];
                                }
                        }
                        k++;
                    }
                    else{
                        break;
                    }
                }

                // multiply the current CTM by the previous CTM
                Mat tempResult;
                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            tempResult.mat[ii][jj]=m.mat[ii][jj];
                            m.mat[ii][jj] = 0;
                        }
                }
                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            for(int kk=0;kk<4;kk++){
                                m.mat[ii][jj]+= tempResult.mat[ii][kk]*prev_m.mat[kk][jj];
                            }
                        }
                }
                // always push
                mstack.push(m);
                i++;
            }
            else if((strcmp(token[j][i],"}"))==0){
                // always pop
                mstack.pop();
                i++;

            }

            ////////////////
            // wire/frame //
            ////////////////
            else if((strcmp(token[j][i],"wire"))==0){
                fill = false;
                i++;
            }
            else if((strcmp(token[j][i],"filled"))==0){
                fill = true;
                i++;
            }

            ////////////////////
            // Render Section //
            ////////////////////
            else if((strcmp(token[j][i],"polygon"))==0){
                Mat tempResult;
                Mat CTM;
                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        tempResult.mat[ii][jj]=mstack.top().mat[ii][jj];
                        CTM.mat[ii][jj]=0;
                    }
                }

                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            for(int kk=0;kk<4;kk++){
                                CTM.mat[ii][jj]+= world_m.mat[ii][kk]*tempResult.mat[kk][jj];
                            }
                        }
                }

                float temp_x1 = atof(token[j][i+1]);
                float temp_y1 = atof(token[j][i+2]);
                float temp_z1 = atof(token[j][i+3]);
                float temp_x2 = atof(token[j][i+4]);
                float temp_y2 = atof(token[j][i+5]);
                float temp_z2 = atof(token[j][i+6]);
                float temp_x3 = atof(token[j][i+7]);
                float temp_y3 = atof(token[j][i+8]);
                float temp_z3 = atof(token[j][i+9]);

                x1 = temp_x1*CTM.mat[0][0]+temp_y1*CTM.mat[0][1]+temp_z1*CTM.mat[0][2]+CTM.mat[0][3];
                y1 = temp_x1*CTM.mat[1][0]+temp_y1*CTM.mat[1][1]+temp_z1*CTM.mat[1][2]+CTM.mat[1][3];
                z1 = temp_x1*CTM.mat[2][0]+temp_y1*CTM.mat[2][1]+temp_z1*CTM.mat[2][2]+CTM.mat[2][3];
                x2 = temp_x2*CTM.mat[0][0]+temp_y2*CTM.mat[0][1]+temp_z2*CTM.mat[0][2]+CTM.mat[0][3];
                y2 = temp_x2*CTM.mat[1][0]+temp_y2*CTM.mat[1][1]+temp_z2*CTM.mat[1][2]+CTM.mat[1][3];
                z2 = temp_x2*CTM.mat[2][0]+temp_y2*CTM.mat[2][1]+temp_z2*CTM.mat[2][2]+CTM.mat[2][3];
                x3 = temp_x3*CTM.mat[0][0]+temp_y3*CTM.mat[0][1]+temp_z3*CTM.mat[0][2]+CTM.mat[0][3];
                y3 = temp_x3*CTM.mat[1][0]+temp_y3*CTM.mat[1][1]+temp_z3*CTM.mat[1][2]+CTM.mat[1][3];
                z3 = temp_x3*CTM.mat[2][0]+temp_y3*CTM.mat[2][1]+temp_z3*CTM.mat[2][2]+CTM.mat[2][3];

                if(fill==true){
                    depthCuePolygonRenderer(x1,y1,z1,x2,y2,z2,x3,y3,z3,nearColour,farColour);
                }
                else{
                    Bresenham(x1,y1,x2,y2,0xffffffff,0xffffffff);
                    Bresenham(x1,y1,x3,y3,0xffffffff,0xffffffff);
                    Bresenham(x2,y2,x3,y3,0xffffffff,0xffffffff);
                }

                i++;
            }
            else if((strcmp(token[j][i],"mesh"))==0){
                Mat tempResult;
                Mat CTM;
                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        tempResult.mat[ii][jj]=mstack.top().mat[ii][jj];
                        CTM.mat[ii][jj]=0;
                    }
                }

                for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                            for(int kk=0;kk<4;kk++){
                                CTM.mat[ii][jj]+= world_m.mat[ii][kk]*tempResult.mat[kk][jj];
                            }
                        }
                }

                meshRenderer(token[j][i+1], CTM,nearColour,farColour);
                i++;
            }
            else break;

        }
    }

    return true;
}

bool Client::meshRenderer(const char* filename, Mat m, unsigned int nearColour, unsigned int farColour){
    ifstream fin;

    fin.open((char*)filename);// open mesh file
    if(fin.fail()){// check if open successfully
        QTextStream(stdout) << "file open error.."<<endl;
        return false;
    }

    const char* tempTok[MAX_TOKENS][MAX_TOKENS] = {}; // initialize to 0
    int lineCount=0;
    const char* token[MAX_TOKENS][MAX_TOKENS] = {};

    while(!fin.eof()){
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];

        fin.getline(buf, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index

        tempTok[lineCount][n] = strtok(buf, DELIMITER); // first token

        if (tempTok[lineCount][0]) // zero if line is blank
        {
          for (n = 1; n < MAX_TOKENS; n++)
          {
            tempTok[lineCount][n] = strtok(NULL, DELIMITER); // subsequent tokens
            if (!tempTok[lineCount][n]) break; // no more tokens
          }
        }

        int i =0;
        // process (print) the tokens
        for (i; i < n; i++){
          token[lineCount][i] = strdup(tempTok[lineCount][i]);
        }
        token[lineCount][i] = "~";
        lineCount++;
    }

    fin.close();
    //////////////////////
    // parsing complete //
    //////////////////////

    int row = atoi(token[0][0]);
    int col = atoi(token[1][0]);
    int meshSize = row*col;
    QTextStream(stdout)<<"MESH"<<endl;

    meshPixel grid_points[row][col];
    int colCounter=2;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QTextStream(stdout)<<m.mat[i][j]<<" ";
        }
        QTextStream(stdout)<<" "<<endl;
    }

    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            grid_points[i][j].x = atoi(token[colCounter][0]);
            grid_points[i][j].y = atoi(token[colCounter][1]);
            grid_points[i][j].z = atoi(token[colCounter][2]);
            colCounter++;

        }
        QTextStream(stdout)<<" "<<endl;
    }

     //transoform teh grid points by CTM
    for(int i=0; i<row; i++){
        for(int j=0;j<col;j++){
            float temp_x1 = grid_points[i][j].x;
            float temp_y1 = grid_points[i][j].y;
            float temp_z1 = grid_points[i][j].z;

            grid_points[i][j].x = temp_x1*m.mat[0][0]+temp_y1*m.mat[0][1]+temp_z1*m.mat[0][2]+m.mat[0][3];
            grid_points[i][j].y = temp_x1*m.mat[1][0]+temp_y1*m.mat[1][1]+temp_z1*m.mat[1][2]+m.mat[1][3];
            grid_points[i][j].z = temp_x1*m.mat[2][0]+temp_y1*m.mat[2][1]+temp_z1*m.mat[2][2]+m.mat[2][3];
            QTextStream(stdout)<<grid_points[i][j].x<<" "<<grid_points[i][j].y<<" "<<grid_points[i][j].z<<" ";
        }
        QTextStream(stdout)<<" "<<endl;
    }
    for(int i=0; i<row;i++){
        for (int j=0;j<col-1;j++){
            if(j<col && i<row-1){
                depthCuePolygonRenderer(grid_points[i][j].x,grid_points[i][j].y,grid_points[i][j].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,nearColour,farColour);
                depthCuePolygonRenderer(grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,grid_points[i+1][j+1].x,grid_points[i+1][j+1].y,grid_points[i+1][j+1].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,nearColour,farColour);
            }
        }
    }

    return true;
}

