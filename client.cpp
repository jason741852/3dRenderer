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
#include "LineDrawer.h"

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
        //PageNumber(5);
        break;
    case 6:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        //PageNumber(6);
        break;
    case 7:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        //PageNumber(7);
        break;
    case 8:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect( 50,  50, 700, 700, 0x00000000);
        drawable->updateScreen();
        //PageNumber(8);
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
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i][j+1].x,gird_point[i][j+1].y,colour1,colour2,drawable);
                }
                if(i<9){
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i+1][j].x,gird_point[i+1][j].y,colour1,colour2,drawable);
                }
                if(i!=0 && i<=9 && j<9){
                    Bresenham(gird_point[i][j].x,gird_point[i][j].y,gird_point[i-1][j+1].x,gird_point[i-1][j+1].y,colour1,colour2,drawable);
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
                    PolygonRenderer(gird_point[i][j].x,gird_point[i][j].y,gird_point[i][j+1].x,gird_point[i][j+1].y,gird_point[i+1][j].x,gird_point[i+1][j].y,colour1,colour2,colour3,drawable);
                    PolygonRenderer(gird_point[i+1][j].x,gird_point[i+1][j].y,gird_point[i+1][j+1].x,gird_point[i+1][j+1].y,gird_point[i][j+1].x,gird_point[i][j+1].y,colour3,colour1,colour2,drawable);
                }
            }
        }
    }
    else if(page_location==3){

        char* filename[] = {"Custom_language_samples/page3.txt"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==4){

        char* filename[] = {"Custom_language_samples/page4.txt"};
        SimpDrawer(filename, 0xff00CC66, 0xff008040);
    }
    else if(page_location==5){
        char* filename[] = {"Custom_language_samples/page5.txt"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==6){
        char* filename[] = {"Custom_language_samples/test1.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==7){
        char* filename[] = {"Custom_language_samples/test2.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
    else if(page_location==8){
        char* filename[] = {"Custom_language_samples/test3.simp"};
        SimpDrawer(filename, 0xffffffff, 0x00000000);
    }
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

    Mat camera; // camera is initilized to be a 4x4 identity matrix if nothing changes

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
                    depthCuePolygonRenderer(x1,y1,z1,x2,y2,z2,x3,y3,z3,nearColour,farColour,drawable);
                }
                else{
                    Bresenham(x1,y1,x2,y2,0xffffffff,0xffffffff,drawable);
                    Bresenham(x1,y1,x3,y3,0xffffffff,0xffffffff,drawable);
                    Bresenham(x2,y2,x3,y3,0xffffffff,0xffffffff,drawable);
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

            else if(strcmp(token[j][i],"camera")==0){

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
                depthCuePolygonRenderer(grid_points[i][j].x,grid_points[i][j].y,grid_points[i][j].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,nearColour,farColour,drawable);
                depthCuePolygonRenderer(grid_points[i+1][j].x,grid_points[i+1][j].y,grid_points[i+1][j].z,grid_points[i+1][j+1].x,grid_points[i+1][j+1].y,grid_points[i+1][j+1].z,grid_points[i][j+1].x,grid_points[i][j+1].y,grid_points[i][j+1].z,nearColour,farColour,drawable);
            }
        }
    }

    return true;
}
