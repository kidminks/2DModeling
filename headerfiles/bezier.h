#ifndef BEZIER_H_INCLUDED
#define BEZIER_H_INCLUDED

class Bezier{
private:
    struct point{
        double x,y;
    };
    point mul(point p,double t){
        point r;
        r.x = p.x*t;
        r.y = p.y*t;
        return r;
    }
    point p[5];
    void markPoints(int color, int t){
        setcolor(color);
        for(int i=0;i<4;i++){
            if(i==t){
                continue;
            }
            circle(p[i].x,p[i].y,3);
        }
        if(t<4&&t>=0){
            setcolor(RED);
            circle(p[t].x,p[t].y,3);
        }
        setcolor(WHITE);
    }
    void getPoints(){
        int c = 0,x,y;
        while(c<4){
            while(!ismouseclick(WM_LBUTTONDOWN)){
            }
            getmouseclick(WM_LBUTTONDOWN,x,y);
            p[c].x=x;p[c].y=y;
            circle(x,y,3);
            c+=1;
        }
        markPoints(BLACK,-10);
    }
    void makeBezierCurve(int color){
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
            time += 0.001;
        }
    }
    void startEdit(int t){
        while(true){
            if(kbhit){
                char c = getch();
                if(c=='b'){
                    return;
                }
                makeBezierCurve(BLACK);
                markPoints(BLACK,-10);
                if(c==KEY_LEFT){
                    p[t].x -= 1;
                }else if(c==KEY_RIGHT){
                    p[t].x += 1;
                }else if(c==KEY_UP){
                    p[t].y -= 1;
                }else if(c==KEY_DOWN){
                    p[t].y += 1;
                }
                makeBezierCurve(WHITE);
                markPoints(GREEN,t);
            }
        }
    }
    void editBezierCurve(){
        markPoints(GREEN,-10);
        while(true){
            if(kbhit){
                char c = getch();
                if(c=='b'){
                    return;
                }
                if(c>='0'&&c<='3'){
                    int t = c-'0';
                    startEdit(t);
                }
            }
        }
    }
    void writeText(int color){
        setcolor(color);
        outtextxy(10,10,"Mark four points using mouse");
        outtextxy(500,10,"Use 0 to 3 to choose the point");
        outtextxy(10,30,"Use arrow key to control after that");
        outtextxy(500,30,"Use b to exit the current state");
        setcolor(WHITE);
    }
public:
    void make(int color){
        makeBezierCurve(color);
    }
    void edit(){
        editBezierCurve();
        makeBezierCurve(BLACK);
        markPoints(BLACK,-10);
    }
    void start(){
        writeText(WHITE);
        getPoints();
        makeBezierCurve(WHITE);
        editBezierCurve();
        makeBezierCurve(BLACK);
        markPoints(BLACK,-10);
        writeText(BLACK);
    }

};


#endif // BEZIER_H_INCLUDED
