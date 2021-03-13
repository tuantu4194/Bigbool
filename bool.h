#ifndef PROGS_LIBRARY_H
#define PROGS_LIBRARY_H

#include <stdio.h>
#include <stdint.h>

#define MAX_PARTS 20

//Error codes
#define NO_ERR 0
#define ERR_EMPTY_VECTOR 1
#define ERR_BAD_STRING -2
#define ERR_SMALL_SHIFT -4
#define ERR_BAD_ARG 2
#define ERR_NULL_ARG 3
#define ERR_EMPTY_STR 5

typedef struct BigBool
{
    uint8_t vector[MAX_PARTS]; // 20
    size_t num_part;
    size_t num_bit;
} BigBool;



 
 /* Return:
        1) NO_ERR if all work properly
        2) ERR_NULL_ARG if BB == NULL
 */   
int BB_reset(BigBool *BB); // set all bit to 0
{
    if (BB == NULL) 
    {
        return ERR_NULL_ARG;
    }
    memset(BB->vector, 0, MAX_PARTS);
    BB->num_bit = 0;
    BB->num_part = 0;
    return NO_ERR;
}


 
 /* Return:
        1) NO_ERR if all work properly,
        2) ERR_NULL_ARG if BB == NULL,
        3) ERR_BAD_ARG if input number bad,
 */
int BB_reverse_bits(BigBool *BB, int sBit, int eBit) // reverse BB from sBit to eBit
{
    if (BB == NULL) 
    {
        return ERR_NULL_ARG;
    }
    if ( sBit < 0 || eBit > MAX_PARTS*8 || sBit > eBit) 
    {
        return ERR_BAD_ARG;
    }
    BigBool tmp;
    if (eBit/8 > BB->num_part) // if amount part > than amount part BB, set part BB to new
    {
        BB->num_part = eBit / 8;
    } 
    memcpy(&tmp, BB, MAX_PARTS); // BB save in tmp   
    for(int pos = sBit; pos < eBit; pos++) 
    {
        tmp.vector[pos / 8] = tmp.vector[pos / 8] & ~(1 << (pos % 8));
        tmp.vector[pos / 8] |= get_bit(BB, (eBit - pos + sBit - 1)) << (pos % 8);
    }
    memcpy(BB, &tmp, MAX_PARTS);
    return NO_ERR;
}

/* 
   
 Returns:
        1) ERR_OK if function work properly,
        2) ERR_NULL_ARG if BB == NULL,
        3) ERR_EMPTY_VECTOR if strlen(str) == 0,
        4) ERR_BAD_STRING if string is not only '1' and '0'.
 */
int BB_from_str(char* str , BigBool* res ) // convert string with char '0' and '1' to vecto bool

    {

    if (res == NULL) 
    {
        return ERR_NULL_ARG;
    }

    size_t len = strlen(str);
    if(len == 0) 
    {
        return ERR_EMPTY_VECTOR;
    }
    memset(res->vector, 0, MAX_PARTS);
    size_t num_part = len / 8;
    size_t num_bit = len % 8;

    res->num_part = num_part;
    res->num_bit = num_bit;

    size_t index = 0;

    for(size_t part = 0; part < num_part; part++) 
    {
        for (size_t bit = 0; bit < 8; bit++) 
        {
            index = len - 1 - (part * 8 + bit);
            if(str[index] != '0' && str[index] != '1') 
            {
                return ERR_BAD_STRING;
            }
            res->vector[part] |= ((str[index] - '0') << bit);
        }
    }

    for(size_t bit = 0; bit < num_bit; bit++) 
    {
        index = len - 1 - (num_part * 8 + bit);
        if (str[index] != '0' && str[index] != '1') 
        {
            return ERR_BAD_STRING;
        }
        res->vector[num_part] |= ((str[index] - '0') << bit);

    }
    return NO_ERR;
}

/*
 * Function: int BB_from_uint64(uint64_t num , BigBool* res) use to Convert Unsigned Long Integer (64 bit) to big bool Vecter
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_NULL_ARG if res == NULL.
 */

int BB_from_uint64(uint64_t num , BigBool* res) 
{

    if (res == NULL)
    {
        return ERR_NULL_ARG;
    }
    memset(res->vector, 0, MAX_PARTS);

    for (int i = 0; i < 8; i++) 
    {
        res->vector[i] |= (num >> 8 * i);
    }

    int pos = high_bit_pos_cycle(num);
    res->num_part = pos / 8;
    res->num_bit = pos % 8;
    return NO_ERR;
};

/*
 * Function: char* BB_to_str(BigBool* res) covert a BB vecto to string '0' and '1'
 * Returns:
        1) Pointer to string,
        2) NULL, if failed to allocate.
 */
char* BB_to_str(BigBool* res)
{

    size_t len = len_bits(BB);

    char* str = (char*)malloc(len*sizeof(char));
    if (str == NULL)
    {
        return NULL;
    }

    for (int strPos = 0; strPos < len; strPos++)
    {
        str[len - strPos - 1] = '0' + get_bit(BB, strPos);
    }
    str[len] = '\0';

    return str;
}

/*
 * Function: int BB_disjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
 
 * Description:  find BB1 or BB1
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_disjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
{

    if (BB1 == NULL || res == NULL || BB2 == NULL)
    {
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2))
    {
        return BB_disjunction(BB2, BB1, res);
    }

    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for(size_t part = 0; part <= BB2->num_part; part++)
    {
        res->vector[part] = BB1->vector[part] | BB2->vector[part];
    }
    for(size_t bit = BB2->num_part + 1; bit <= BB1->num_part; bit++) 
    {
        res->vector[bit] = BB1->vector[bit];
    }

    return NO_ERR;
}

/*
 * Function: int BB_conjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
 
 * Description:  find BB1 and BB2
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_conjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
{

    if (BB1 == NULL || res == NULL || BB2 == NULL) 
    {
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2)) 
    {
        return BB_conjunction(BB2, BB1, res);
    }
    memset(res->vector, 0, MAX_PARTS);
    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for (int pos = 0; pos < len_bits(BB2); pos++) 
    {
        res->vector[pos / 8] |= (get_bit(BB1, pos) & get_bit(BB2, pos)) << (pos % 8);
    }
    for (int pos = len_bits(BB2); pos < len_bits(BB1); pos++) 
    {
        res->vector[pos / 8] |= get_bit(BB1, pos) << (pos % 8);
    }
    return NO_ERR;
}

/*
 * Function: int BB_xor (BigBool* BB1, BigBool* BB2, BigBool* res)
 * Description:  find BB1 xor BB2
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_xor (BigBool* BB1, BigBool* BB2, BigBool* res)
{

    if (BB1 == NULL || res == NULL || BB2 == NULL) 
    {
        return ERR_BAD_ARG;
    }
    if(len_bits(BB1) < len_bits(BB2)) 
    {
        return BB_xor(BB2, BB1, res);
    }

    res->num_part = BB1->num_part;
    res->num_bit = BB1->num_bit;

    for(size_t part = 0; part <= BB2->num_part; part++) 
    {
        res->vector[part] = BB1->vector[part] ^ BB2->vector[part];
    }
    for(size_t part = BB2->num_part + 1; part <= BB1->num_part; part++)
    {
        res->vector[part] = BB1->vector[part];
    }
    return NO_ERR;
}

/*
 * Function: int BB_inversion (BigBool* BB1, BigBool* res)
 
BB * Description:   makes inversion of bool vector ( ~BB ) 
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_inversion (BigBool* BB1, BigBool* res)
{

    if (BB1 == NULL || res == NULL) 
    {
        return ERR_BAD_ARG;
    }
    res->num_bit = BB1->num_bit;
    res->num_part = BB1->num_part;

    for (int part = 0; part <= BB1->num_part; part++)
    {
        res->vector[part] = ~BB1->vector[part];
    }

    return NO_ERR;
}

/*
 * Function: int BB_left_shift (BigBool* BB, BigBool* res, size_t len_shift)
 
 * Description:  do left shift number input ( << integer )
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) ERR_BIG_SHIFT if len of shift is bigger than len of vector,
        4) ERR_SMALL_SHIFT if len of shift less than 0.
 */
int BB_left_shift (BigBool* BB, BigBool* res, int len_shift)
{
    if (BB == NULL || res == NULL || len_shift < 0) 
    {
        return ERR_BAD_ARG;
    }
    if (len_shift >= MAX_PARTS*8) 
    {
        memset(res->vector, 0, MAX_PARTS);
        res->num_bit = 1;
        res->num_part = 0;
    }
    else 
    {
        size_t sizeNew = len_bits(BB) + len_shift;

        res->num_part = sizeNew / 8;
        res->num_bit = sizeNew % 8;

        size_t LastNew = res->num_part + (res->num_bit > 0) - 1;

        for (size_t part = LastNew; part > len_shift / 8; part--)
        {
            uint8_t first_byte = BB->vector[part - len_shift / 8 - 1] >> (8 - len_shift % 8);
            res->vector[part] = BB->vector[part - len_shift / 8];
            res->vector[part] <<= len_shift % 8;
            res->vector[part] |= first_byte;
        }

        res->vector[len_shift / 8] = BB->vector[0];
        res->vector[len_shift / 8] <<= len_shift % 8;

        for (size_t part = 0; part < len_shift / 8; part++)
        {
            res->vector[part] = 0;
        }
        res->vector[len_shift / 8] >>= len_shift % 8;
        res->vector[len_shift / 8] <<= len_shift % 8;
    }
    return NO_ERR;
}

/*
 * Function: int BB_right_shift (BigBool* BB, BigBool* res, size_t len_shift)
 
 * Description:  do left shift number input ( >> integer )
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) ERR_BIG_SHIFT if len of shift is bigger than len of vector,
        4) ERR_SMALL_SHIFT if len of shift less than 0.
 */
int BB_right_shift (BigBool* BB, BigBool* res, int len_shift)
{

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
    return NO_ERR;
}

/*
 * Function: int BB_cyclic_left_shift (BigBool* BB, BigBool** res, size_t len_shift)
 
 * Description: do cyclic left shift of bool vector
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) BB_cyclic_right_shift(BB, res, -len_shift) if len of shift less than 0,
 *
 */
int BB_cyclic_left_shift (BigBool* BB, BigBool* res, int len_shift)
{
    if (BB == NULL || res == NULL) 
    {
        return ERR_BAD_ARG;
    }
    if (len_shift < 0) 
    {
        return BB_cyclic_right_shift(BB, res, -len_shift);
    }
    len_shift %= len_bits(BB);
    memcpy(res, BB, MAX_PARTS);
    res->num_bit = BB->num_bit;
    res->num_part = BB->num_part;
    BB_reverse_bits(res, len_bits(res)-len_shift, len_bits(res));
    BB_reverse_bits(res, 0, len_bits(res)-len_shift);
    BB_reverse_bits(res, 0, len_bits(res));
    return NO_ERR;
};

/*
 * Function: int BB_cyclic_right_shift (BigBool*BB, BigBool** res, size_t len_shift)
 
 * Description: do cyclic right shift of bool vector
 
 * Returns:
        ) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) BB_cyclic_left_shift(BB, res, -len_shift) if len of shift less than 0,
 *
 */
int BB_cyclic_right_shift (BigBool*BB, BigBool* res, int len_shift)
{
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
}

#endif //PROGS_LIBRARY_H
