#include <iostream>
#include <graphics.h>
#include <cmath>
#include <string>
using namespace std;
#define PI 3.14159265

struct point{
    double x,y;
};

point mul(point p, double t){
    point r;
    r.x = p.x*t;
    r.y = p.y*t;
    return r;
}

void markPoints(point p[], int color, int t){
    setcolor(color);
    for(int i=0;i<4;i++){
        if(i==t){
            continue;
        }
        circle(p[i].x,p[i].y,2);
    }
    if(t<4&&t>=0){
        setcolor(RED);
        circle(p[t].x,p[t].y,2);
    }
    setcolor(WHITE);
}

void getPoints(point p[]){
    int c = 0,x,y;
    while(c<4){
        while(!ismouseclick(WM_LBUTTONDOWN)){
        }
        getmouseclick(WM_LBUTTONDOWN,x,y);
        p[c].x=x;p[c].y=y;
        c+=1;
    }
}

void makeBezierCurve(point p[], int color){
    point r[5];
    double time = 0;
    while(time<1){
        r[0] = mul(p[0],(1-time)*(1-time)*(1-time));
        r[1] = mul(p[1],3*time*(1-time)*(1-time));
        r[2] = mul(p[2],3*time*time*(1-time));
        r[3] = mul(p[3],time*time*time);
        double x = r[0].x+r[1].x+r[2].x+r[3].x;
        double y = r[0].y+r[1].y+r[2].y+r[3].y;
        putpixel(x,y,color);
        time += 0.0225;
    }
}

point* startEdit(point p[],int t){
    while(true){
        if(kbhit){
            char c = getch();
            if(c=='b'){
                return p;
            }
            makeBezierCurve(p,BLACK);
            markPoints(p,BLACK,-10);
            if(c==KEY_LEFT){
                p[t].x -= 1;
            }else if(c==KEY_RIGHT){
                p[t].x += 1;
            }else if(c==KEY_UP){
                p[t].y -= 1;
            }else if(c==KEY_DOWN){
                p[t].y += 1;
            }
            makeBezierCurve(p,WHITE);
            markPoints(p,GREEN,t);
        }
    }
}

void editBezierCurve(point p[]){
    while(true){
        if(kbhit){
            char c = getch();
            if(c=='b'){
                return;
            }
            if(c>='0'&&c<='3'){
                int t = c-'0';
                p = startEdit(p,t);
            }
        }
    }
}


int main()
{
    initwindow(1525,800);
    outtextxy(10,10,"Mark four points using mouse");
    outtextxy(500,10,"Use 0 to 3 to choose the point");
    outtextxy(10,30,"Use arrow key to control after that");
    outtextxy(500,30,"Use b to exit the current state");
    point p[5];
    getPoints(p);
    makeBezierCurve(p,15);
    markPoints(p,GREEN,-10);
    editBezierCurve(p);
    closegraph();
    return 0;
}
