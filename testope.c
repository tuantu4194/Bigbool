  
#include"bool.c"

#include<stdio.h>
#include<string.h>

int TestOrOperation1()
{
    int temp = 0;
    BigBool result, result1, res;

    BB_from_str("0011", &result);
    BB_from_str("1010", &result1);
    BB_disjunction(&result, &result1, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "1011") != 0){
        printf("0011 & 1010  != 1011\n");
        printf ("Error in  1 test\n");
        temp++;
    }

    free((void*)string);
    return temp;
};

int TestAndOperation2()
{
    int temp = 0;
    BigBool result, result1, res;
    BB_from_str("1011", &result); // len_vector = 26
    BB_from_str("1101", &result1);   // len_vector = 21
    BB_conjunction(&result, &result1, &res);
    char* string = BB_to_str(&res);
    if (strcmp (string, "1001") != 0){
        printf("1011 & 1101  != 1001\n");
        printf ("Error in  2 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
};

int TestXorOperation3()
{
    int temp = 0;
    BigBool result, result1, res;
    BB_from_str("1010", &result);
    BB_from_str("0100", &result1);
    BB_xor(&result, &result1, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "1110") != 0){
        printf("1010 & 0100 != 1110\n");
        printf ("Error in 3 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
};

int TestNotOperation4()
{
    int temp = 0;
    BigBool result, res;

    BB_from_str("0100", &result);
    BB_inversion(&result, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "1011") != 0){
        printf("~0000  != 1011\n");
        printf ("Error in  4 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
};

int Test_Right_Shift5() {

    int temp = 0;
    BigBool result, res;

    BB_from_str("1010", &result);
    BB_right_shift(&result, &res, 2);

    char *string = BB_to_str(&res);

    if (strcmp(string, "10") != 0) {
        printf("(1010 >> 2)  != 10\n");
        printf ("Error in  5 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_Left_Shift6() {

    int temp = 0;
    BigBool res, result;
    BB_from_str("1110", &result);
    BB_left_shift(&result, &res, 2);

    char *string = BB_to_str(&res);

    if (strcmp(string, "111000") != 0) {
        printf("(1110 >> 2)  != 111000\n");
        printf ("Error in  6 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_Cycle_Shifts7(){

    int temp = 0;

    BigBool result, res;

    BB_from_str("1001", &result);
    BB_cyclic_left_shift(&result, &res, 3);

    char *string = BB_to_str(&res);

    if (strcmp(string, "1100") != 0) {
        printf("(1001 << 3)   != 1100\n");
        printf ("Error in  7 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_Right_Cycle_Shift8(){

    int temp = 0;

    BigBool result, res;

    BB_from_str("1001", &result);
    BB_cyclic_right_shift(&result, &res, 3);

    char *string = BB_to_str(&res);
    if (strcmp(string, "0011") != 0) {
        printf("(1001 >> 3)  != 0011\n");
        printf ("Error in  8 test\n");
        temp++;
    }

    free((void *)string);
    return temp;
};

int main (){
    int response = 0;
    response += TestOrOperation1();
    response += TestAndOperation2();
    response += TestXorOperation3();
    response += TestNotOperation4();
    response += Test_Right_Shift5();
    response += Test_Left_Shift6();
    response += Test_Cycle_Shifts7();
    response += Test_Right_Cycle_Shift8();

    if(response != 0){
        printf("Ammount of faild test = %d\n", response);
        return 0;
    }
    puts("This test with len_vector = 4 work properly");
    return 0;
}
