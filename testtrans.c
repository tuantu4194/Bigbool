
#include "bool.c"

#include <stdio.h>
#include <string.h>
#include <time.h>


int Trans_BB_Test(){
    int temp = 0;

    BigBool res1, res2;

    uint64_t num = 4477799;
    BB_from_uint64(num, &res1);

    BB_from_str("10001000101001101100111", &res2);

    char* string = BB_to_str(&res2);
    char* str = BB_to_str(&res1);
    if (strcmp (string, str) != 0){
        printf("Transformers don't work properly\n");
        temp++;
    }

    free((void*)string);
    free((void*)str);

    return temp;
};

int Random_De_Morgan_Test(){
    int temp = 0;

    srand (time (NULL));
    BigBool test1, test2, res1, not_res1, not_res2, DeMorgan;

    BB_from_uint64(rand(), &test1);
    BB_from_uint64(rand(), &test2);

    // res1 | res2
    BB_disjunction(&test1, &test2, &res1);
    // ~(res1 | res2)
    BB_inversion(&res1, &not_res1);
    char* str_left_part = BB_to_str(&not_res1);

    BB_reset(&res1);
    BB_reset(&not_res1);

    // ~test1
    BB_inversion(&test1, &not_res1);
    // ~test2
    BB_inversion(&test2, &not_res2);

    // ~test1 & ~test2
    BB_conjunction(&not_res1, &not_res2, &DeMorgan);

    char* str_right_part = BB_to_str(&DeMorgan);
    if(strcmp(str_left_part, str_right_part) != 0){
        printf("~(x or y) not equal ((~x) & (~y))");
        temp++;
    }

    free((void*)str_left_part);
    free((void*)str_right_part);

    return temp;
};

int Random_Xor_Test(){

    int temp = 0;

    srand (time (NULL));

    BigBool test1, test2, not_res1, not_res2, fst_part, snd_part;

    BB_from_uint64(rand(), &test1);
    BB_from_uint64(rand(), &test2);

    //xor test1 ^ test2
    BB_xor(&test1, &test2, &not_res1);
    char* str_vec_xor = BB_to_str(&not_res1);
    BB_reset(&not_res1);

    // ~test1
    BB_inversion(&test1, &not_res1);
    // ~test2
    BB_inversion(&test2, &not_res2);
    //1st part ~test1 & test2
    BB_conjunction(&not_res1, &test2, &fst_part);
    //2nd part test1 & ~test2
    BB_conjunction(&test1, &not_res2, &snd_part);
    BB_reset(&not_res1);
    BB_disjunction(&fst_part, &snd_part, &not_res1);
    char* str_end_result = BB_to_str(&not_res1);

    if (strcmp(str_vec_xor,str_end_result) != 0){
    printf("(x xor y) not equal ((~x & y) | (x & ~y))");
    temp++;
    }

    free((void*)str_vec_xor);
    free((void*)str_end_result);

    return temp;
};
int main (){
    int response = 0;

    // Test function transformation
    response += Trans_BB_Test();
    response += Random_De_Morgan_Test();
    response += Random_Xor_Test();

    if(response != 0){
        printf("Ammount of faild test = %d\n", response);
        return 0;
    }
    puts("This test work properly");
    return 0;
}
