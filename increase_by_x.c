#include "inc.h"
int increase_by_x(int n,int x){
    if (x%2==0)
        return n-x;
    else
        return n+x;
}