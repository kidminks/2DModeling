#ifndef OBJECTMAKER_H_INCLUDED
#define OBJECTMAKER_H_INCLUDED
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "bezier.h"
#include "hermite.h"
#include "imageRending.h"
using namespace std;

class ObjectMaker{
private:
    vector<Bezier> b;
    vector<Hermite> h;
    vector<ImageRender> image;
    string saveLocation;

    void makeObject(int color){
        for(int i=0;i<image.size();i++){
            image[i].make(BLACK);
        }
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
    void startImage() {
        ImageRender imageRender;
        imageRender.start();
        image.push_back(imageRender);
        makeObject(WHITE);
    }
    void editCurve(){
        int editCurve = -2;
        char c;
        for(int i=0;i<b.size();i++){
            b[i].make(BLACK);
            b[i].make(GREEN);
            B:
            while(!kbhit()){
            }
            c = getch();
            if(c=='b'){
                return;
            }
            if(c==KEY_RIGHT){
                b[i].make(BLACK);
                b[i].make(WHITE);
            }else if(c=='e'){
                b[i].make(BLACK);
                b[i].make(WHITE);
                editCurve = i;
                break;
            }else if(c=='d'){
                b[i].make(BLACK);
                b.erase(b.begin()+i);
            }else{
                goto B;
            }
        }
        if(editCurve!=-2){
            b[editCurve].edit();
            return;
        }
        for(int i=0;i<h.size();i++){
            h[i].make(BLACK);
            h[i].make(GREEN);
            H:
            while(!kbhit()){
            }
            c = getch();
            if(c=='b'){
                return;
            }
            if(c==KEY_RIGHT){
                h[i].make(BLACK);
                h[i].make(WHITE);
            }else if(c=='e'){
                h[i].make(BLACK);
                h[i].make(WHITE);
                editCurve = i;
                break;
            }else if(c=='d'){
                h[i].make(BLACK);
                h.erase(h.begin()+i);
            }else{
                goto H;
            }
        }
        if(editCurve!=-2){
            h[editCurve].edit();
        }
        for(int i=0;i<image.size();i++){
            image[i].make(BLACK);
            image[i].make(GREEN);
            I:
            while(!kbhit()){
            }
            c = getch();
            if(c=='b'){
                return;
            }
            if(c==KEY_RIGHT){
                image[i].make(BLACK);
                image[i].make(WHITE);
            }else if(c=='e'){
                image[i].make(BLACK);
                image[i].make(WHITE);
                editCurve = i;
                break;
            }else if(c=='d'){
                cleardevice();
                image.erase(image.begin()+i);
                makeObject(WHITE);
            }else{
                goto I;
            }
        }
        if(editCurve!=-2){
            image[editCurve].edit();
            return;
        }
    }
    void decide(int i){
        switch(i){
            case 1: startBerzier();break;
            case 2: startHermite();break;
            case 3: startImage();break;
            case 4: editCurve();break;
        }
    }
    void setSaveFile(){
        string s,l="../saves/";
        cout<<"Write file name :- ";
        cin >> s;
        s += ".txt";
        saveLocation = l+s;
        cout<<saveLocation<<' ';
    }
public:
    ObjectMaker(){
        saveLocation = "";
    }
    void writeText(int color){
        setcolor(color);
        outtextxy(10,10,"Use 1 for Bezier 2 for Hermite and 3 to add image 4 to edit");
        outtextxy(10,30,"Use b to exit, s to save, r to read");
        outtextxy(10,50,"see terminal after pressing s or r");
        setcolor(WHITE);
    }
    void save(){
        ofstream o;
        if(saveLocation==""){
            setSaveFile();
        }
        o.open(saveLocation,ios::out);
        for(int i=0;i<b.size();i++){
            b[i].save(&o);
        }
        for(int i=0;i<h.size();i++){
            h[i].save(&o);
        }
        for(int i=0;i<image.size();i++){
            image[i].save(&o);
        }
        cout<<"saved"<<endl;
    }
    void read(){
        ifstream i;
        string s,l="../saves/";
        cout<<"Write file name (see saves directory):- ";
        cin >> s;
        s += ".txt";
        cout<<s<<' ';
        i.open(l+s,ios::in);
        double num = 0.0;
        vector<double> v;
        while(i >> num){
            if(num==3.0){
                ImageRender imageRender;
                v.clear();
                for(int it=0;it<4;it++){
                    i >> num;
                    v.push_back(num);
                }
                string s;
                i >> s;
                imageRender.pointForImage(v,s);
                image.push_back(imageRender);
            }else if(num==1.0){
                Bezier bezier;
                v.clear();
                for(int it=0;it<8;it++){
                    i >> num;
                    v.push_back(num);
                }
                bezier.pointForCurve(v);
                b.push_back(bezier);
            }else if(num==2.0){
                Hermite hermite;
                v.clear();
                for(int it=0;it<10;it++){
                    i >> num;
                    v.push_back(num);
                }
                hermite.pointForCurve(v);
                h.push_back(hermite);
            }
        }
        cout<<"read"<<endl;
        writeText(BLACK);
        writeText(WHITE);
    }
    void start(int t){
            makeObject(WHITE);
            writeText(BLACK);
            decide(t);
            writeText(WHITE);
    }
};

#endif // OBJECTMAKER_H_INCLUDED
