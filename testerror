#include"bool.c"

#include<stdio.h>
#include<string.h>

int Test1(){
    int temp = 0;

    BigBool res;

    if (BB_from_str("01794z", &res) != ERR_BAD_STRING){
        printf ("Did't set ERR_BAD_STRING\n");
        temp++;
    }

    return temp;
};

int Test2() {
    int temp = 0;

    BigBool result;
    BigBool *res = NULL;
    BB_from_str("1011110100", &result);

    if (BB_left_shift(&result, res, -4) != ERR_BAD_ARG){
        printf("Didn't set ERR_BAD_ARG\n");
        temp++;
    }

    free(res);
    return temp;
};

int Test3(){

    int temp = 0;

    BigBool res, result;
    BB_from_str("101001011110", &result);

    if (BB_left_shift(&result, &res, 3) == ERR_BAD_ARG){
        printf("Didn't set ERR_BAD_ARG\n");
        temp++;
    }

    if (BB_right_shift(&result, &res, 2) == ERR_BAD_ARG){
        printf("Didn't set ERR_BAD_ARG\n");
        temp++;
    }
    if (BB_cyclic_right_shift(&result, &res, 2) == ERR_BAD_ARG){
        printf("Didn't set ERR_BAD_ARG\n");
        temp++;
    }
    if (BB_cyclic_left_shift(&result, &res, 2) == ERR_BAD_ARG){
        printf("Didn't set ERR_BAD_ARG\n");
        temp++;
    }

    return temp;
};

int main (){
    int response = 0;
// Test errors in all functions
    response += Test1();

// Test errors in Shift
    response += Test2();
    response += Test3();

    if(response != 0){
        printf("Ammount of faild test = %d\n", response);
        return 0;
    }
    puts("This test of errors work properly");
    return 0;
}
