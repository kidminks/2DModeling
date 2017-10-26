#ifndef IMAGERENDING_H_INCLUDED
#define IMAGERENDING_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ImageRender{
private:
    vector<double> p;
    string filename;
    void mark(int color){
        setcolor(color);
        rectangle(p[0]-3,p[1]-3,p[2]+3,p[3]+3);
        setcolor(WHITE);
    }
    void getImage(int color){
        cleardevice();
        string f = "../image/"+filename;
        char t[50];
        int i;
        for(i=0;i<f.size();i++){
            t[i] = f.at(i);
        }
        t[i]='\0';
        readimagefile(t, p[0],p[1],p[2],p[3] );
        mark(color);
    }
    void scaleImage(){
        char c;
        S:
        while(!kbhit()){
        }
        c = getch();
        if(c==KEY_RIGHT){
            p[2] += 5;
        }else if(c==KEY_LEFT){
            p[2] -= 5;
        }else if(c==KEY_UP){
            p[3] += 5;
        }else if(c==KEY_DOWN){
            p[3] -= 5;
        }
        if(c!='b'){
            getImage(GREEN);
            goto S;
        }
    }
    void translate(){
        char c;
        T:
        while(!kbhit()){
        }
        c = getch();
        if(c==KEY_RIGHT){
            p[0] += 5;
            p[2] += 5;
        }else if(c==KEY_LEFT){
            p[0] -= 5;
            p[2] -= 5;
        }else if(c==KEY_UP){
            p[1] -= 5;
            p[3] -= 5;
        }else if(c==KEY_DOWN){
            p[1] += 5;
            p[3] += 5;
        }
        if(c!='b'){
            getImage(GREEN);
            goto T;
        }
    }
    void setImage(){
        writeText(WHITE);
        char c;
        while(!kbhit()){
        }
        c = getch();
        if(c!='c'){
            writeText(BLACK);
            return;
        }
        cout<<" Enter filename in image dir :- ";
        cin >> filename;
        p.push_back(70);
        p.push_back(70);
        p.push_back(400);
        p.push_back(400);
    }
    void writeText(int color){
        setcolor(color);
        outtextxy(10,10,"c to choose from images");
        outtextxy(500,10,"any other key to skip");
        outtextxy(10,30,"Press s and arrow to scale");
        outtextxy(500,30,"Press t and arrow to translate");
        setcolor(WHITE);
    }
public:
    void save(ofstream* o){
        *o<<3<<' ';
        for(int i=0;i<4;i++){
            *o << p[i] <<' ';
        }
        *o << filename;
        *o<<'\n';
    }
    void pointForImage(vector<double> v,string f){
        for(int i = 0;i<v.size();i++){
            p.push_back(v[i]);
        }
        filename = f;
        getImage(BLACK);
    }
    void edit(){
        char c;
        getImage(GREEN);
        P:
        writeText(WHITE);
        while(!kbhit()){
        }
        c = getch();
        if(c=='s'){
            scaleImage();
        }else if(c=='t'){
            translate();
        }
        if(c!='b'){
            goto P;
        }
    }
    void make(int color){
        getImage(color);
    }
    void start(){
        setImage();
        edit();
    }
};

#endif // IMAGERENDING_H_INCLUDED
