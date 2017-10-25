#include <iostream>
#include <graphics.h>
#include "../headerfiles/objectMaker.h"
using namespace std;
int main(){
    initwindow(1525,800);
    ObjectMaker objectMaker;
    objectMaker.writeText(WHITE);
    while(true){
        if(kbhit()){
            char c = getch();
            if(c=='b'){
                break;
            }
            if(c=='s'){

            }
            if(c>='1'&&c<='3'){
                objectMaker.start(c-'0');
            }
        }
    }
    closegraph();
    return 0;
}
