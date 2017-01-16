#include <math.h>
#include <QTextStream>
#include <stdlib.h>

#include "LineDrawer.h"

// Digital Differential Analyzer Algorithm
// Check if the slope value is between -1 and 1
// If so increment/decrement y along x++ or x--
// Otherwise if slope is not between -1 and 1
// Increment/decrement x along y++ or y--


void DDA(float x1, float y1, float x2, float y2, unsigned int color, Drawable *drawable){
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
void Bresenham(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2, Drawable *drawable){
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



void PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color1, unsigned int color2, unsigned int color3, Drawable *drawable){
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

                    Bresenham(x,long_y,x,a_y,current_Color1,current_Color2,drawable);
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
                    Bresenham(x,long_y,x,b_y,current_Color1,current_Color3,drawable);
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

                    Bresenham(x,long_y,x,a_y,current_Color1,current_Color2,drawable);
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

                    Bresenham(x,long_y,x,b_y,current_Color1,current_Color3,drawable);
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

                    Bresenham(long_x,y,a_x,y,current_Color1,current_Color2,drawable);
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

                    Bresenham(long_x,y,b_x,y,current_Color1,current_Color3,drawable);
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

                    Bresenham(long_x,y,a_x,y,current_Color1,current_Color2,drawable);
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

                    Bresenham(long_x,y,b_x,y,current_Color1,current_Color3,drawable);
                }
            }
        }
    }

}


int Distance(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}




void depthCuePolygonRenderer(int x1,int y1,int z1, int x2, int y2, int z2, int x3, int y3, int z3, unsigned int nearColor, unsigned farColor, Drawable *drawable){
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

        PolygonRenderer(x1,y1,x2,y2,x3,y3,current_Color1,current_Color2,current_Color3,drawable);
    }
}

