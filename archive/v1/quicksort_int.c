#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdio.h> // Defines scanf() and printf().
#include <stdlib.h> // Defines atoi(), atof(), rand().
#include <math.h> // Defines math functions such as exp(x,y).
#include <time.h> // Defines time.
#include <string.h> // obv
#include <assert.h> // obv
#include <errno.h> // Defines some explicit errors to aid in debugging.

boolean full_screen = FALSE;

void item_exchange_int(int *a, int i1, int i2){
    int m = a[i1];
    a[i1] = a[i2];
    a[i2] = m;
}

int median_three(int *a, size_t nitems, int (*compare)(int, int)){
    int pivot = nitems/2;
    if (compare(a[0], a[nitems-1])==0)
        item_exchange_int(a,0,nitems-1);
    if(nitems<3)
        return a[pivot];
    if (compare(a[0], a[pivot])==0)
        item_exchange_int(a,0,pivot);
    if (compare(a[nitems-1], a[pivot]))
        item_exchange_int(a,nitems-1,pivot);
    return a[pivot];
}

void quicksort_int_r(int *a, size_t nitems, int (*compare)(int, int)){
    int pivot = median_three(a,nitems,compare);
    if (nitems>3){
        item_exchange_int(a, nitems/2, nitems-1);
        int left = 0;
        int right = nitems-1;
        printf("pivot:%d\n", pivot);
        while (left<=right){
            while(left<=right&&compare(a[left],pivot)){left++;};
            while(left<=right&&compare(a[right],pivot)==0){right--;}; //Is this really the best way to loop??
            if(left>=right)
                break;
            item_exchange_int(a, left, right);
            left++;
            right--;
        };
        item_exchange_int(a, left, nitems-1);
        quicksort_int_r(a,left, compare); // How will I divide this?
        quicksort_int_r(a+left, nitems-left, compare);
    }
}

void quicksort_int(int *a, int low, int high, int (*compare)(int, int)){
    quicksort_int_r(a+low, high, compare);
}

int less_than(int a, int b){
    return a<b;
}

int main() {
    int n = 6;
    int a[6] = {4,6,2,5,1,3};
    quicksort_int(a,0,n,less_than);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}