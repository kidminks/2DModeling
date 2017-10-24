#include <iostream>
#include <graphics.h>
#include <cmath>
#include <string>
using namespace std;
#define PI 3.14159265

struct point{
    double x,y;
};
struct tangent{
    double x,y;
    double theta;
};



point mul(point p, double t){
    point r;
    r.x = p.x*t;
    r.y = p.y*t;
    return r;
}
point mul(tangent p, double t){
    point r;
    r.x = p.x*t;
    r.y = p.y*t;
    return r;
}
tangent rotation(tangent t){
    double c = cos(t.theta*PI/180.0), s = sin(t.theta*PI/180.0);
    double x = t.x*c+t.y*s;
    double y = -t.x*s+t.y*c;
    t.x = x;
    t.y = y;
    return t;
}
void marker(point p[], tangent t[], int color){
    setcolor(color);
    putpixel(p[0].x,p[0].y,color);
    putpixel(p[1].x,p[1].y,color);
    line(p[0].x,p[0].y,p[0].x+t[0].x/2,p[0].y+t[0].y/2);
    line(p[1].x,p[1].y,p[1].x+t[1].x/2,p[1].y+t[1].y/2);
    setcolor(WHITE);
}
void getPoints(point p[]){
    int c = 0,x,y;
    while(c<2){
        while(!ismouseclick(WM_LBUTTONDOWN)){
        }
        getmouseclick(WM_LBUTTONDOWN,x,y);
        p[c].x=x;p[c].y=y;
        c+=1;
    }
}
double calculateTheta(point p[]){
    double pro = (p[1].y-p[0].y)/(p[1].x-p[0].x);
    return atan(pro)*180/PI;
}
void makeHermiteCurve(point p[], tangent t[], int color){
    point r[5];
    double time = 0;
    while(time<1){
        r[0] = mul(p[0],(1+2*time)*(1-time)*(1-time));
        r[1] = mul(p[1],time*time*(3-2*time));
        r[2] = mul(t[0],time*(1-time)*(1-time));
        r[3] = mul(t[1],time*time*(time-1));
        double x = r[0].x+r[1].x+r[2].x+r[3].x;
        double y = r[0].y+r[1].y+r[2].y+r[3].y;
        putpixel(x,y,color);
        time += 0.001;
    }
}


void editHermiteCurve(point p[], tangent t[]){
    while(true){
        if(kbhit){
            char c = getch();
            if(c=='b'){
                return;
            }
            makeHermiteCurve(p,t,0);
            marker(p,t,BLACK);
            if(c=='w'){
                t[0].x += 1;
                t[0].y += tan(t[0].theta*PI/180.0);
            }
            else if(c=='s'){
                t[0].x -= 1;
                t[0].y -= tan(t[0].theta*PI/180.0);
            }
            else if(c==KEY_UP){
                t[1].x += 1;
                t[1].y += tan(t[1].theta*PI/180.0);;
            }
            else if(c==KEY_DOWN){
                t[1].x -= 1;
                t[1].y -= tan(t[1].theta*PI/180.0);;
            }
            else if(c=='a'){
                t[0].theta = t[0].theta+1;
                if(t[0].theta==361){
                    t[0].theta = 0;
                }
                t[0] = rotation(t[0]);
            }
            else if(c=='d'){
                t[0].theta = t[0].theta-1.0;
                t[0] = rotation(t[0]);
                if(t[0].theta<=0){
                    t[0].theta = 360-t[0].theta;
                }
            }
            else if(c==KEY_LEFT){
                t[1].theta = t[1].theta+1;
                if(t[1].theta==361){
                    t[1].theta = 0;
                }
                t[1] = rotation(t[1]);
            }
            else if(c==KEY_RIGHT){
                t[1].theta = t[1].theta-1;
                t[1] = rotation(t[1]);
                if(t[1].theta<=0){
                    t[1].theta = 360-t[1].theta;
                }
            }
            makeHermiteCurve(p,t,15);
            marker(p,t,GREEN);
        }
    }
}

int main()
{
    initwindow(1525,800);
    outtextxy(10,10,"Mark two points using mouse");
    outtextxy(500,10,"Use a and d to rotate tangent from first point");
    outtextxy(10,30,"Use w and s to increase or decrease tangent from first point");
    outtextxy(500,30,"Use up and down to increase or decrease tangent from second point");
    outtextxy(10,50,"Use left and right to rotate tangent from second point");
    outtextxy(500,50,"Green line represent tangent :P");
    point p[3];
    tangent t[3];
    t[0].x = 0;
    t[0].y = 0;
    t[1].x = 0;
    t[1].y = 0;
    getPoints(p);
    t[0].theta = t[1].theta = calculateTheta(p);
    makeHermiteCurve(p,t,15);
    editHermiteCurve(p,t);
    closegraph();
    return 0;
}
