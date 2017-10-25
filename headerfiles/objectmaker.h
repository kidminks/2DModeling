#ifndef OBJECTMAKER_H_INCLUDED
#define OBJECTMAKER_H_INCLUDED
#include <vector>
#include "bezier.h"
#include "hermite.h"
using namespace std;
class ObjectMaker{
private:
    vector<Bezier> b;
    vector<Hermite> h;
    void makeObject(int color){
        for(int i=0;i<b.size();i++){
            b[i].make(color);
        }
        for(int i=0;i<h.size();i++){
            h[i].make(color);
        }
        setcolor(WHITE);
    }
    void startBerzier(){
        Bezier berzier;
        berzier.start();
        b.push_back(berzier);
        makeObject(WHITE);
    }
    void startHermite(){
        Hermite hermite;
        hermite.start();
        h.push_back(hermite);
        makeObject(WHITE);
    }
    void editCurve(){
        int editCurve = -2;
        for(int i=0;i<b.size();i++){
            b[i].make(BLACK);
            b[i].make(GREEN);
            while(true){
                if(kbhit()){
                    char c = getch();
                    if(c==KEY_RIGHT){
                        b[i].make(BLACK);
                        b[i].make(WHITE);
                        break;
                    }else if(c=='e'){
                        b[i].make(BLACK);
                        b[i].make(WHITE);
                        editCurve = i;
                        i = b.size();
                        break;
                    }else if(c=='d'){
                        b[i].make(BLACK);
                        b.erase(b.begin()+i);
                        break;
                    }
                }
            }
        }
        if(editCurve!=-2){
            b[editCurve].edit();
            return;
        }
        for(int i=0;i<h.size();i++){
            h[i].make(BLACK);
            h[i].make(GREEN);
            while(true){
                if(kbhit()){
                    char c = getch();
                    if(c==KEY_RIGHT){
                        h[i].make(BLACK);
                        h[i].make(WHITE);
                        break;
                    }else if(c=='e'){
                        h[i].make(BLACK);
                        h[i].make(WHITE);
                        editCurve = i;
                        i = h.size();
                        break;
                    }else if(c=='d'){
                        h[i].make(BLACK);
                        h.erase(h.begin()+i);
                        break;
                    }
                }
            }
        }
        if(editCurve!=-2){
            b[editCurve].edit();
            return;
        }
    }
    void decide(int i){
        switch(i){
            case 1: startBerzier();break;
            case 2: startHermite();break;
            case 3: editCurve();
        }
    }
public:
    void writeText(int color){
        setcolor(color);
        outtextxy(10,10,"Use 1 for Bezier 2 for Hermite and 3 to edit curve");
        outtextxy(10,30,"Use b to exit and s to save");
        setcolor(WHITE);
    }
    void start(int t){
            makeObject(WHITE);
            writeText(BLACK);
            decide(t);
            writeText(WHITE);
    }
};

#endif // OBJECTMAKER_H_INCLUDED
