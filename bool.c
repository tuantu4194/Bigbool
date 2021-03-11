#include "bool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


size_t len_bits(BigBool* BB){
    return BB->num_part * 8 + BB->num_bit;
}

int BB_reset(BigBool *BB)  // set all to 0
{
    if (BB == NULL) {
        return ERR_NULL_ARG;
    }
    memset(BB->vector, 0, MAX_PARTS);
    BB->num_bit = 0;
    BB->num_part = 0;
    return ERR_OK;
}

int printBB(BigBool* BB) {
    size_t num_part = BB->num_part;
    size_t num_bit = BB->num_bit;
    printf("Num parts:\t%d\nNum bit:\t%d\n", num_part, num_bit); // print amount bit and part

    for (size_t bit = num_bit; bit > 0; bit--) {
        printf("%d", ((BB->vector[num_part]) >> (bit-1) & 1)); // print all bit
    }

    for (size_t part = num_part; part > 0; part--) {
        for (size_t bit = 8; bit > 0; bit--) {
            printf("%d", ((BB->vector[part-1]) >> (bit-1) & 1)); // print all part (all part will print from bit 8 -> bit 0
        }
    }

    puts("");
    return ERR_OK;
}


int get_bit(BigBool *BB, int pos) // return bit with input int number
{
    return (BB->vector[pos / 8] >> (pos % 8) & 1);
}

int BB_reverse_bits(BigBool *BB, int startBit, int endBit) // đảo ngược
{
    if (BB == NULL) 
    {
        return ERR_NULL_ARG;
    }
    if ( startBit < 0 || endBit > MAX_PARTS*8 || startBit > endBit) 
    {
        return ERR_BAD_ARG;
    }
    BigBool tmp;
    if (endBit/8 > BB->num_part) // if amount part > than amount part BB, set part BB to new
    {
        BB->num_part = endBit / 8;
    } 
    memcpy(&tmp, BB, MAX_PARTS); // BB save in tmp   
    for(int pos = startBit; pos < endBit; pos++) 
    {
        tmp.vector[pos / 8] = tmp.vector[pos / 8] & ~(1 << (pos % 8));
        tmp.vector[pos / 8] |= get_bit(BB, (endBit - pos + startBit - 1)) << (pos % 8);
    }
    memcpy(BB, &tmp, MAX_PARTS);
    return ERR_OK;
}

int BB_from_str(char* str, BigBool* res) {

    if (res == NULL) {
        return ERR_NULL_ARG;
    }

    size_t len = strlen(str);
    if(len == 0) {
        return ERR_EMPTY_VECTOR;
    }
    memset(res->vector, 0, MAX_PARTS);
    size_t num_part = len / 8;
    size_t num_bit = len % 8;

    res->num_part = num_part;
    res->num_bit = num_bit;

    size_t index = 0;

    for(size_t part = 0; part < num_part; part++) {
        for (size_t bit = 0; bit < 8; bit++) {
            index = len - 1 - (part * 8 + bit);
            if(str[index] != '0' && str[index] != '1') {
                return ERR_BAD_STRING;
            }
            res->vector[part] |= ((str[index] - '0') << bit);
        }
    }

    for(size_t bit = 0; bit < num_bit; bit++) {
        index = len - 1 - (num_part * 8 + bit);
        if (str[index] != '0' && str[index] != '1') {
            return ERR_BAD_STRING;
        }
        res->vector[num_part] |= ((str[index] - '0') << bit);

    }
    return ERR_OK;
};

size_t high_bit_pos_cycle(uint64_t num) {
        size_t bytes = 0;
        size_t bits = 0;
        while ((num >> ((bytes + 1) * 8)) != 0)
            bytes++;
        while ((num >> (bytes * 8 + bits)) != 0)
            bits++;
        return bytes * 8 + bits;
};

int BB_from_uint64(uint64_t num, BigBool* res){

    if (res == NULL){
        return ERR_NULL_ARG;
    }
    memset(res->vector, 0, MAX_PARTS);

    for (int i = 0; i < 8; i++) {
        res->vector[i] |= (num >> 8 * i);
    }

    int pos = high_bit_pos_cycle(num);
    res->num_part = pos / 8;
    res->num_bit = pos % 8;
    return ERR_OK;
};

char* BB_to_str(BigBool* BB){

    size_t len = len_bits(BB);

    char* str = (char*)malloc(len*sizeof(char));
    if (str == NULL){
        return NULL;
    }

    for (int strPos = 0; strPos < len; strPos++){
        str[len - strPos - 1] = '0' + get_bit(BB, strPos);
    }
    str[len] = '\0';

    return str;
};

int BB_xor (BigBool* BB1, BigBool* BB2, BigBool* res){

    if (BB1 == NULL || res == NULL || BB2 == NULL) {
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2)) {
        return BB_xor(BB2, BB1, res);
    }

    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for(size_t part = 0; part <= BB2->num_part; part++) {
        res->vector[part] = BB1->vector[part] ^ BB2->vector[part];
    }
    for(size_t part = BB2->num_part + 1; part <= BB1->num_part; part++) {
        res->vector[part] = BB1->vector[part];
    }
    return ERR_OK;
};

int BB_disjunction(BigBool* BB1, BigBool* BB2, BigBool* res){

    if (BB1 == NULL || res == NULL || BB2 == NULL){
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2)){
        return BB_disjunction(BB2, BB1, res);
    }

    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for(size_t part = 0; part <= BB2->num_part; part++){
        res->vector[part] = BB1->vector[part] | BB2->vector[part];
    }
    for(size_t bit = BB2->num_part + 1; bit <= BB1->num_part; bit++) {
        res->vector[bit] = BB1->vector[bit];
    }

    return ERR_OK;
};

int BB_conjunction (BigBool* BB1, BigBool* BB2, BigBool* res){

    if (BB1 == NULL || res == NULL || BB2 == NULL) {
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2)) {
        return BB_conjunction(BB2, BB1, res);
    }
    memset(res->vector, 0, MAX_PARTS);
    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for (int pos = 0; pos < len_bits(BB2); pos++) {
        res->vector[pos / 8] |= (get_bit(BB1, pos) & get_bit(BB2, pos)) << (pos % 8);
    }
    for (int pos = len_bits(BB2); pos < len_bits(BB1); pos++) {
        res->vector[pos / 8] |= get_bit(BB1, pos) << (pos % 8);
    }
    return ERR_OK;
};

int BB_inversion (BigBool* BB1, BigBool* res){

    if (BB1 == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    res->num_bit = BB1->num_bit;
    res->num_part = BB1->num_part;

    for (int part = 0; part <= BB1->num_part; part++){
        res->vector[part] = ~BB1->vector[part];
    }

    return ERR_OK;
};

int BB_left_shift(BigBool* BB, BigBool* res, int len_shift){
    if (BB == NULL || res == NULL || len_shift < 0) {
        return ERR_BAD_ARG;
    }
    if (len_shift >= MAX_PARTS*8) {
        memset(res->vector, 0, MAX_PARTS);
        res->num_bit = 1;
        res->num_part = 0;
    }
    else {
        size_t sizeNew = len_bits(BB) + len_shift;

        res->num_part = sizeNew / 8;
        res->num_bit = sizeNew % 8;

        size_t LastNew = res->num_part + (res->num_bit > 0) - 1;

        for (size_t part = LastNew; part > len_shift / 8; part--){
            uint8_t first_byte = BB->vector[part - len_shift / 8 - 1] >> (8 - len_shift % 8);
            res->vector[part] = BB->vector[part - len_shift / 8];
            res->vector[part] <<= len_shift % 8;
            res->vector[part] |= first_byte;
        }

        res->vector[len_shift / 8] = BB->vector[0];
        res->vector[len_shift / 8] <<= len_shift % 8;

        for (size_t part = 0; part < len_shift / 8; part++){
            res->vector[part] = 0;
        }
        res->vector[len_shift / 8] >>= len_shift % 8;
        res->vector[len_shift / 8] <<= len_shift % 8;
    }
    return ERR_OK;
};

int BB_right_shift (BigBool* BB, BigBool* res, int len_shift){

    if (BB == NULL || res == NULL || len_shift < 0) {
        return ERR_BAD_ARG;
    }
    if (len_shift >= len_bits(BB)) {
        memset(res->vector, 0, MAX_PARTS);
        res->num_bit = 1;
        res->num_part = 0;
    }
    else {
        size_t last_part = BB->num_part + (BB->num_bit > 0) - 1;
        size_t  sizeNew = len_bits(BB) - len_shift;

        res->num_part = sizeNew / 8;
        res->num_bit = sizeNew % 8;

        size_t LastNew = last_part - len_shift / 8;

        for (size_t part = 0; part < LastNew; part++)
        {
            uint8_t first_byte = BB->vector[part + len_shift / 8 + 1] << (8 - len_shift % 8);
            res->vector[part] = BB->vector[part + len_shift / 8];
            res->vector[part] >>= len_shift % 8;
            res->vector[part] |= first_byte;
        }

        res->vector[LastNew] = BB->vector[LastNew + len_shift / 8];
        res->vector[LastNew] >>= len_shift % 8;
    }
    return ERR_OK;
};

int BB_cyclic_left_shift (BigBool* BB, BigBool* res, int len_shift) {
    if (BB == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    if (len_shift < 0) {
        return BB_cyclic_right_shift(BB, res, -len_shift);
    }
    len_shift %= len_bits(BB);
    memcpy(res, BB, MAX_PARTS);
    res->num_bit = BB->num_bit;
    res->num_part = BB->num_part;
    BB_reverse_bits(res, len_bits(res)-len_shift, len_bits(res));
    BB_reverse_bits(res, 0, len_bits(res)-len_shift);
    BB_reverse_bits(res, 0, len_bits(res));
    return ERR_OK;
};

int BB_cyclic_right_shift (BigBool* BB, BigBool* res, int len_shift){
    if (BB == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    int shift_amount;
    if (len_shift < 0) {
        shift_amount = -len_shift;
    }
    else {
        shift_amount = len_bits(BB) - len_shift;
    }
    return BB_cyclic_left_shift(BB, res, shift_amount);
};
