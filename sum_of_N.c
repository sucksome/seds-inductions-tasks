#include <stdio.h>
#include "inc.h"
int main(){
    int n;
    printf("Enter value for n: ");
    scanf("%d",&n);
    int sum=0;
    for(int i=0;i<n+1;i++){
        sum=increase_by_x(sum,i);
    }
    printf("Sum of first %d elements of the series is: %d\n",n,sum);
}