#ifndef HERMITE_H_INCLUDED
#define HERMITE_H_INCLUDED
#include <cmath>
using namespace std;
#define PI 3.14159265

class Hermite{
private:
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
    point p[3];
    tangent t[3];
    void marker(int color){
        setcolor(color);
        circle(p[0].x,p[0].y,3);
        circle(p[1].x,p[1].y,3);
        //line(p[0].x,p[0].y,p[0].x+t[0].x,p[0].y+t[0].y);
        //line(p[1].x,p[1].y,p[1].x+t[1].x,p[1].y+t[1].y);
        setcolor(WHITE);
    }
    void getPoints(){
        int c = 0,x,y;
        while(c<2){
            while(!ismouseclick(WM_LBUTTONDOWN)){
            }
            getmouseclick(WM_LBUTTONDOWN,x,y);
            p[c].x=x;p[c].y=y;
            circle(x,y,3);
            c+=1;
        }
        marker(BLACK);
    }
    double calculateTheta(){
        double pro = (p[1].y-p[0].y)/(p[1].x-p[0].x);
        return atan(pro)*180/PI;
    }
    void makeHermiteCurve(int color){
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
    void editHermiteCurve(){
        makeHermiteCurve(15);
        char c;
        P:
        while(!kbhit()){
        }
        c = getch();
        if(c=='b'){
            return;
        }else{
            makeHermiteCurve(0);
            marker(BLACK);
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
            makeHermiteCurve(15);
            marker(GREEN);
            goto P;
        }
    }
    void writeText(int color){
        setcolor(color);
        outtextxy(10,10,"Mark two points using mouse");
        outtextxy(500,10,"Use a and d to rotate tangent from first point");
        outtextxy(10,30,"Use w and s to increase or decrease tangent from first point");
        outtextxy(500,30,"Use up and down to increase or decrease tangent from second point");
        outtextxy(10,50,"Use left and right to rotate tangent from second point");
        outtextxy(500,50,"Green line represent tangent :P");
        setcolor(WHITE);
    }
public:
    void make(int color){
        makeHermiteCurve(color);
    }
    void edit(){
        editHermiteCurve();
        marker(BLACK);
    }
    void save(ofstream* o){
        *o<<2<<' ';
        for(int i=0;i<2;i++){
            *o<<p[i].x<<' '<<p[i].y<<' '<<t[i].x<<' '<<t[i].y<<' '<<t[i].theta<<' ';
        }
        *o<<'\n';
    }
    void pointForCurve(vector<double> v){
        int k = 0;
        for(int i=0;i<v.size();i += 5){
            p[k].x = v[i];
            p[k].y = v[i+1];
            t[k].x = v[i+2];
            t[k].y = v[i+3];
            t[k].theta = v[i+4];
            k += 1;
        }
        makeHermiteCurve(WHITE);
    }
    void start(){
        writeText(WHITE);
        t[0].x = 0;
        t[0].y = 0;
        t[1].x = 0;
        t[1].y = 0;
        getPoints();
        t[0].theta = t[1].theta = calculateTheta();
        makeHermiteCurve(WHITE);
        marker(GREEN);
        editHermiteCurve();
        makeHermiteCurve(0);
        marker(BLACK);
        writeText(BLACK);
    }
};

#endif // HERMITE_H_INCLUDED
