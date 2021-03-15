#include"bool.h"

#include<stdio.h>
#include<string.h>

int Test1(){    //test trans
    int temp = 0;

    BigBool res1, res2;

    uint64_t testnum = 2111200068869999;
    BB_from_uint64(testnum, &res1);

    BB_from_str("111100000000010000000010010001001111001111101101111", &res2);

    char* string = BB_to_str(&res2);
    char* str = BB_to_str(&res1);
    if (strcmp (string, str) != 0){
        printf("There are error in Transformers \n");
        temp++;
    }

    free((void*)string);
    free((void*)str);

    return temp;
};

};

int TestOr()
{
    int temp = 0;
    BigBool BB1, BB2, res;

    BB_from_str("10010000111001000100001000001001000100111100000110000100101010100000110", &BB1);
    BB_from_str("1010010111100011111100101010000101010101000111001010101010101001111100010010", &BB2);
    BB_disjunction(&BB1, &BB2, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "1010010111100111111100101011000101011101100111101010111010101101111100010110") != 0){
        printf("OR work\n");
        printf ("Error in Or test\n");
        temp++;
    }

    free((void*)string);
    return temp;
};

int TestAnd()
{
    int temp = 0;
    BigBool BB1, BB2, res;

    BB_from_str("10010000111001000100001000001001000100111100000110000100101010100000110", &BB1);
    BB_from_str("1010010111100011111100101010000101010101000111001010101010101001111100010010", &BB2);
    BB_disjunction(&BB1, &BB2, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "10010000011001000100000000001000000000111000000100000100001010100000010") != 0){
        printf("AND work\n");
        printf ("Error in AND test\n");
        temp++;
    }

    free((void*)string);
    return temp;
};

int TestXOR()
{
    int temp = 0;
    BigBool BB1, BB2, res;

    BB_from_str("10010000111001000100001000001001000100111100000110000100101010100000110", &BB1);
    BB_from_str("1010010111100011111100101010000101010101000111001010101010101001111100010010", &BB2);
    BB_disjunction(&BB1, &BB2, &res);

    char* string = BB_to_str(&res);

    if (strcmp (string, "1010000101100100110100001011000100011101100000101010011010001100101000010100") != 0){
        printf("XOR work\n");
        printf ("Error in XOR test\n");
        temp++;
    }

    free((void*)string);
    return temp;
};

int Test_Left_Shift() {

    int temp = 0;
    BigBool res, BB;
    BB_from_str("1110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110", &BB);
    BB_left_shift(&BB, &res, 10);

    char *string = BB_to_str(&res);

    if (strcmp(string, "1011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011100000000000") != 0) {
        printf("Left Shift OK");
        printf ("Error in L_SHIFT test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_Right_Shift() {

    int temp = 0;
    BigBool res, BB;
    BB_from_str("1110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110", &BB);
    BB_left_shift(&BB, &res, 10);

    char *string = BB_to_str(&res);

    if (strcmp(string, "111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011") != 0) {
        printf("Right Shift OK");
        printf ("Error in R_SHIFT test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_CYCLE_Right_Shift() {

    int temp = 0;
    BigBool res, BB;
    BB_from_str("1110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110", &BB);
    BB_Cycle_Right(&BB, &res, 21);

    char *string = BB_to_str(&res);

    if (strcmp(string, "111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111") != 0) {
        printf("CYCLIC Right Shift OK");
        printf ("Error in CYCLE_R_SHIFT test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test_CYCLE_Left_Shift() {

    int temp = 0;
    BigBool res, BB;
    BB_from_str("1110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110", &BB);
    BB_Cycle_Left(&BB, &res, 25);

    char *string = BB_to_str(&res);

    if (strcmp(string, "1101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101110111011101") != 0) {
        printf("CYCLIC LEFT Shift OK");
        printf ("Error in CYCLE_L_SHIFT test\n");
        temp++;
    }

    free((void *)string);

    return temp;
};

int Test2(){ //test operands
    int temp=0;
    temp+=TestOr();
    temp+=TestAnd();
    temp+=TestXOR();
    temp+=Test_Left_Shift();
    temp+=Test_Right_Shift();
    temp+=Test_CYCLE_Right_Shift();
    temp+=Test_CYCLE_Left_Shift();

    return temp;
}


int main (){
    int total = 0;
// Test Trans
    total += Test1();

// Test Operands
    total += Test2();

    if(total != 0){
        printf("Ammount of error test = %d\n", total);
        return 0;
    }
    puts("This test work OK");
    return 0;
}
