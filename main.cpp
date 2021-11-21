#include <iostream>
#include "ternary_app.h"

int main(){
    TernaryApp t1;
    t1.processCommandLine("1,-10,3,8,1,2,3,9,10,11,3,P,L,R,U,M,T,R,C,P,-1,-2,-200,P,T,A,P,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,-999,P,B,0,P");
    return 0;
}