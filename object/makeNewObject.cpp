#include <iostream>
#include <graphics.h>
#include <fstream>
#include <time.h>
#include "../headerfiles/objectMaker.h"
using namespace std;
int main(){
    initwindow(1525,800);
    ObjectMaker objectMaker;
    objectMaker.writeText(WHITE);
    P:
    while(!kbhit()){
    }
    char c = getch();
    if(c=='s'){
        objectMaker.save();
    }
    if(c=='r'){
        objectMaker.read();
    }
    if(c>='1'&&c<='4'){
        int i = 0;
        while(i<10){
            objectMaker.make(BLACK);
            Sleep(100);
            objectMaker.make(WHITE);
            i += 1;
        }
        //objectMaker.start(c-'0');
    }
    if(c!='b'){
        goto P;
    }
    closegraph();
    return 0;
}
