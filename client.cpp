#include <iostream>
#include <math.h>
#include <QTextStream>
#include <iostream>
#include <ctime>
#include "client.h"

# define PI  3.14159265358979323846  /* pi */

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}


void Client::nextPage() {
    static int pageNumber = 0;
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;

    switch(pageNumber % 5) {
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
        break;
    case 3:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        break;
    case 4:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        // fall through...
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
    //QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<"), m= "<<m<<endl;
    // check slope to see which octant
    if(abs(m)>=0 && abs(m)<1)
    {
        //QTextStream(stdout)<<"in I"<<endl;
        int i = 0;
        if(dx>0){
            //QTextStream(stdout)<<"cond. 1"<<endl;
            for(float x = x1; x<x2; x++){
                    y = m*x + b;
                    //QTextStream(stdout)<<"y= "<<y<<" x= "<<x<<" m: "<<m<<endl;
                    drawable->setPixel(x,y,color);
                    i++;
    //                if(i>40)
    //                {
    //                    QTextStream(stdout)<<"pixels drawn: "<<i<<endl;
    //                }
                }

        }
        else{
            //QTextStream(stdout)<<"cond. 2"<<endl;
            for(float x = x1; x>x2; x--){
                    y = m*x + b;
                    //QTextStream(stdout)<<"y= "<<y<<" x= "<<x<<" m: "<<m<<endl;
                    drawable->setPixel(x,y,color);
                    i++;
    //                if(i>40)
    //                {
    //                    QTextStream(stdout)<<"pixels drawn: "<<i<<endl;
    //                }
                }
        }

    }
    else{
        if(dy>0){
            //QTextStream(stdout)<<"cond. 3"<<endl;

            //QTextStream(stdout)<<"in II"<<endl;
            float x;
            for(float y=y1; y<y2; y++){
                x = (y-b)/m;
                //QTextStream(stdout)<<"x= "<<x<<endl;

                drawable->setPixel(x,y,color);
            }
        }
        else{
            //QTextStream(stdout)<<"cond. 4"<<endl;

            //QTextStream(stdout)<<"in II"<<endl;
            float x;
            for(float y=y1; y>y2; y--){
                x = (y-b)/m;
                //QTextStream(stdout)<<"x= "<<x<<endl;

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

     int r1,g1,b1,r2,b2,g2;
    r1 = (color1>>16)& 0xff;
    g1 = (color1>>8) & 0xff;
    b1 = color1 & 0xff;
    r2 = (color2>>16)& 0xff;
    g2 = (color2>>8) & 0xff;
    b2 = color2 & 0xff;

    unsigned int current_Color;



    QTextStream(stdout)<<"r1= "<<r1<<" g1= "<<g1<<" b1= "<<b1<<endl;
    QTextStream(stdout)<<"r2= "<<r2<<" g2= "<<g2<<" b2= "<<b2<<endl;

    //QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<")"<<endl;
    //int y = y1;
    drawable->setPixel(x1,y1,color1);

    if(dx>dy){
        int err = two_dy-dx;
        int t2 = two_dy-two_dx;



        if(y2>y1){
            int y = y1;
            if(x2>x1){
                QTextStream(stdout)<<"1st cond. "<<endl;
                float dr = (r2-r1)/(x2-x1);
                float dg = (g2-g1)/(x2-x1);
                float db = (b2-b1)/(x2-x1);
                QTextStream(stdout)<<"dr= "<<dr<<" dg= "<<dg<<" db= "<<db<<endl;
                // Traverse along x+
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    r1 = round(r1+dr);
                    g1 = round(g1+dg);
                    b1 = round(b1+db);
                    QTextStream(stdout)<<"r1= "<<r1<<" g1= "<<g1<<" b1= "<<b1<<endl;
                    current_Color = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                QTextStream(stdout)<<"2nd cond. "<<endl;
                float dr = (r2-r1)/(x1-x2);
                float dg = (g2-g1)/(x1-x2);
                float db = (b2-b1)/(x1-x2);
                // Traverse along x-
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    r1 = round(r1+dr);
                    g1 = round(g1+dg);
                    b1 = round(b1+db);
                    current_Color = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,current_Color);
                }
            }
        }
        else{
            if(x2>x1){
                QTextStream(stdout)<<"3rd cond. "<<endl;
                float dr = (r2-r1)/(x2-x1);
                float dg = (g2-g1)/(x2-x1);
                float db = (b2-b1)/(x2-x1);
                //QTextStream(stdout)<<"2nd cond. "<<endl;
                int y = y1;
                // Traverse along x+
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    r1 = round(r1+dr);
                    g1 = round(g1+dg);
                    b1 = round(b1+db);
                    current_Color = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,current_Color);
                }
            }
            else{
                QTextStream(stdout)<<"4th cond. "<<endl;
                float dr = (r2-r1)/(x1-x2);
                float dg = (g2-g1)/(x1-x2);
                float db = (b2-b1)/(x1-x2);
                int y = y1;
                // Traverse along x-
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    r1 = round(r1+dr);
                    g1 = round(g1+dg);
                    b1 = round(b1+db);
                    current_Color = (0xff<<24) + ((r1 & 0xff)<<16) + ((g1 & 0xff)<<8) + (b1 & 0xff);
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
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
                    QTextStream(stdout)<<"5th cond. "<<endl;
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    // Traverse along y+
                    for(int y=y1+1; y<=y2; y++){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color1);
                    }
                }
                else{
                    QTextStream(stdout)<<"6th cond. "<<endl;
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    // Traverse along y-
                    for(int y=y1+1; y>=y2; y--){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color1);
                    }
                }
        }
        else{
            if(y2>y1){
                QTextStream(stdout)<<"7th cond. "<<endl;
                int x = x1;
                // Traverse along y+
                for(int y=y1+1; y<=y2; y++){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color1);
                }
            }
            else{
                QTextStream(stdout)<<"8th cond. "<<endl;
                int x = x1;
                // Traverse along y-
                for(int y=y1+1; y>=y2; y--){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color1);
                }
            }
        }
    }
}



//void Client::PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color){
//    // find the left-most point of the triangle label it x1 and y1, call i p1
//    // if p1 is the lowest vertex of the triangle (max y),
//    // assign the the other vertex of the longest line to p2
//    // the last point is p3
//    // so p1 and p3 have either min(x's), max(y's) or min(x's), min(y's)

//    bool VertLine_p1p2 = false;
//    bool VertLine_p1p3 = false;
//    bool VertLine_p2p3 = false;
//    float x1,y1,x2,y2,x3,y3;
//    //QTextStream(stdout)<<"(p1,p2)="<<endl;

//    // Assigning parameters to p1,p2,p3
//    if(Distance(xx1,yy1,xx2,yy2)>=Distance(xx1,yy1,xx3,yy3) && Distance(xx1,yy1,xx2,yy2)>=Distance(xx2,yy2,xx3,yy3)){
//        x1 = xx1;
//        y1 = yy1;
//        x2 = xx2;
//        y2 = yy2;
//        x3 = xx3;
//        y3 = yy3;
//        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

//    }
//    else if(Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx2,yy2) && Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx3,yy3)){
//        x1 = xx2;
//        y1 = yy2;
//        x2 = xx3;
//        y2 = yy3;
//        x3 = xx1;
//        y3 = yy1;
//        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;

////        if(Distance(xx2,yy2,xx1,yy1)>=Distance(xx2,yy2,xx3,yy3)){
////            x2 = xx1;
////            y2 = yy1;
////            x3 = xx3;
////            y3 = yy3;
////        }
////        else{
////            x2 = xx3;
////            y2 = yy3;
////            x3 = xx1;
////            y3 = yy1;
////        }
//    }
//    else{
//        x1 = xx1;
//        y1 = yy1;
//        x2 = xx3;
//        y2 = yy3;
//        x3 = xx2;
//        y3 = yy2;
//        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;

////        if(Distance(xx3,yy3,xx1,yy1)>Distance(xx3,yy3,xx2,yy2)){
////            x2 = xx1;
////            y2 = yy1;
////            x3 = xx2;
////            y3 = yy2;
////        }
////        else{
////            x2 = xx2;
////            y2 = yy2;
////            x3 = xx1;
////            y3 = yy1;
////        }
//    }


////    // flip y so y is always on top (lower to higher)
////    if(y1>y2){
////        temp = x1;
////        x1 = x2;
////        x2 = temp;
////        temp = y1;
////        y1 = y2;
////        y2 = temp;
////    }

//    QTextStream(stdout)<<"(x,y)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;



//    // Declaration for the longest line p1p2
//    float long_dx = x2-x1;
//    float long_dy = y2-y1;
//    float long_m = (float)long_dy/(float)long_dx;
//    float long_b = y1-long_m*x1;
//    float long_y;
//    float long_x;

//    // Declaration for line p1p3
//    float a_dx = x3-x1;
//    float a_dy = y3-y1;
//    float a_m = (float)a_dy/(float)a_dx;
//    float a_b = y1-a_m*x1;
//    float a_x;
//    float a_y;

//    // Declaration for line p2p3
//    float b_dx = x3-x2;
//    float b_dy = y3-y2;
//    float b_m = (float)b_dy/(float)b_dx;
//    float b_b = y2-b_m*x2;
//    float b_x;
//    float b_y;

//    QTextStream(stdout)<<"b_m= "<<b_m<<endl;

//    //Check for vertical slope (m = infinity)
//    if((x1-x2)==0){
//        VertLine_p1p2 = true;
//        QTextStream(stdout)<<"p1p2 inf slope"<<endl;
//    }
//    if((x1-x3)==0){
//        VertLine_p1p3 = true;
//        QTextStream(stdout)<<"p1p3 inf slope"<<endl;
//    }
//    if((x2-x3)==0){
//        VertLine_p2p3 = true;
//        QTextStream(stdout)<<"p2p3 inf slope"<<endl;
//    }

//    // iterate along y
//    int i = 0;
//    //QTextStream(stdout)<<"(y,x)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;
//    QTextStream(stdout)<<"Slope= "<<long_m<<" || x1,y1="<<x1<<","<<y1<<"|| x2,y2="<<x2<<","<<y2<<"|| x3,y3="<<x3<<","<<y3<<endl;
//    if(!(abs(long_m)>0) && !(abs(long_m)<1)){
//        if(y1>y2){
//            QTextStream(stdout)<<"ONE"<<endl;
//            for(float y = y1; y>=y2; y--){
//                //QTextStream(stdout)<<"(x,y)=( "<<y<<","<<long_x<<endl;
//                if(y<y3){
//                    //QTextStream(stdout)<<"ONE"<<endl;
//                    //QTextStream(stdout)<<"long_x= "<<long_x<<endl;
//                    if(!VertLine_p1p2){
//                        long_x = (y-long_b)/long_m;
//                    }
//                    else{
//                        long_x = x2;
//                    }
//                    if(!VertLine_p1p3){
//                        a_x = (y-a_b)/a_m;
//                    }
//                    else{
//                        a_x = x1;
//                    }
//                    QTextStream(stdout)<<"(x,y)=( "<<long_x<<","<<y<<") to (a_x,a_y)=("<<a_x<<","<<y<<")"<<endl;
//                    Bresenham(long_x,y,a_x,y,color);
//                }
//                else{
//                    //QTextStream(stdout)<<"TWO"<<endl;
//                    if(!VertLine_p1p2){
//                        long_x = (y-long_b)/long_m;
//                    }
//                    else{
//                        long_x = x2;
//                    }
//                    if(!VertLine_p2p3){
//                        b_x = (y-b_b)/b_m;
//                    }
//                    else{
//                        b_x = x2;
//                    }
//                    QTextStream(stdout)<<"b_x= "<<b_x<<endl;
//                    QTextStream(stdout)<<"(x,y)=("<<long_x<<","<<y<<") to (b_x,b_y)=("<<b_x<<","<<y<<")"<<endl;
//                    Bresenham(long_x,y,b_x,y,color);
//                }
//                i++;
//            }
//        }
//        else{
//            QTextStream(stdout)<<"TWO"<<endl;
//            for(float y = y1; y<=y2; y++){
//                //QTextStream(stdout)<<"(x,y)=( "<<y<<","<<long_x<<endl;
//                if(y>y3){

//                    //QTextStream(stdout)<<"THREE"<<endl;
//                    //QTextStream(stdout)<<"long_x= "<<long_x<<endl;
//                    if(!VertLine_p1p2){
//                        long_x = (y-long_b)/long_m;
//                    }
//                    else{
//                        long_x = x2;
//                    }
//                    if(!VertLine_p1p3){
//                        a_x = (y-a_b)/a_m;
//                    }
//                    else{
//                        a_x = x1;
//                    }
//                    QTextStream(stdout)<<"(x,y)=( "<<y<<","<<long_x<<") to (a_x,a_y)=("<<a_x<<","<<y<<")"<<endl;
//                    Bresenham(long_x,y,a_x,y,color);
//                }
//                else{
//                    //QTextStream(stdout)<<"FOUR"<<endl;
//                    if(!VertLine_p1p2){
//                        long_x = (y-long_b)/long_m;
//                        QTextStream(stdout)<<"long_m= "<<long_m<<endl;
//                    }
//                    else{
//                        long_x = x2;
//                    }
//                    if(!VertLine_p2p3){
//                        b_x = (y-b_b)/b_m;
//                    }
//                    else{
//                        b_x = x2;
//                    }
//                    //QTextStream(stdout)<<"b_x= "<<b_x<<endl;
//                    QTextStream(stdout)<<"(x,y)=("<<long_x<<","<<y<<") to (b_x,b_y)=("<<b_x<<","<<y<<")"<<endl;
//                    Bresenham(long_x,y,b_x,y,color);
//                }
//                i++;
//            }
//        }
//    }
//    else{
//        if(x1>x2){
//            QTextStream(stdout)<<"THREE"<<endl;
//            for(float x= x1; x>=x2; x--){
//                //QTextStream(stdout)<<"(y,x)"<<endl;
//                if(x>x3){
//                    //QTextStream(stdout)<<"FIVE"<<endl;
//                    //QTextStream(stdout)<<"long_y= "<<long_y<<endl;
//                    long_y = long_m*x + long_b;
//                    if(!VertLine_p1p3){
//                        a_y = a_m*x + a_b;
//                    }
//                    else{
//                        a_y=y3;
//                    }
//                    Bresenham(x,long_y,x,a_y,color);
//                }
//                else{
//                    //QTextStream(stdout)<<"SIX"<<endl;
//                    //QTextStream(stdout)<<"long_y= "<<long_y<<endl;
//                    long_y = long_m*x + long_b;
//                    if(!VertLine_p2p3){
//                        b_y = b_m*x + b_b;
//                    }
//                    else{
//                        b_y = y2;
//                    }
//                    Bresenham(x,long_y,x,b_y,color);
//                }
//                i++;
//            }
//        }
//        else{
//            QTextStream(stdout)<<"FOUR"<<endl;
//            for(float x= x1; x<=x2; x++){
//                //QTextStream(stdout)<<"(y,x)"<<endl;
//                if(x<x3){
//                    //QTextStream(stdout)<<"SEVEN"<<endl;
//                    //QTextStream(stdout)<<"long_y= "<<long_y<<endl;
//                    long_y = long_m*x + long_b;
//                    if(!VertLine_p1p3){
//                        a_y = a_m*x + a_b;
//                    }
//                    else{
//                        a_y=y3;
//                    }
//                    Bresenham(x,long_y,x,a_y,color);
//                }
//                else{
//                    //QTextStream(stdout)<<"EIGHT"<<endl;
//                    //QTextStream(stdout)<<"long_y= "<<long_y<<endl;
//                    long_y = long_m*x + long_b;
//                    if(!VertLine_p2p3){
//                        b_y = b_m*x + b_b;
//                    }
//                    else{
//                        b_y = y2;
//                    }
//                    Bresenham(x,long_y,x,b_y,color);
//                }
//                i++;
//            }
//        }
//    }
//}

void Client::PageNumber(int page_position){
    Bresenham(100,200,600,400,0x11bef7,0xFF5F3B);
    QTextStream(stdout)<<"ran";

}

int Client::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
