#include <iostream>
#include <graphics.h>
#include "../headerfiles/objectMaker.h"
using namespace std;

int main(){
    initwindow(1525,800);
    ObjectMaker objectMaker[3];
    objectMaker[0].read("gandhi1");
    objectMaker[1].read("gandhi2");
    double k = -2;
    for(int i = 0;i<200;i++ ){
        if(i%2==0){
            objectMaker[0].make(WHITE);
            Sleep(200);
        }else{
            objectMaker[1].make(WHITE);
            Sleep(200);
        }
        cleardevice();
        objectMaker[0].translateObject(k,0);
        objectMaker[1].translateObject(k,0);
    }
    return 0;
}
