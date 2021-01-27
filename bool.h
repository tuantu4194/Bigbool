#ifndef PROGS_LIBRARY_H
#define PROGS_LIBRARY_H

#include <stdio.h>
#include <stdint.h>

#define MAX_PARTS 20

//Error codes
#define ERR_OK 0
#define ERR_EMPTY_VECTOR 1
#define ERR_BAD_STRING -2
#define ERR_SMALL_SHIFT -4
#define ERR_BAD_ARG 2
#define ERR_NULL_ARG 3
#define ERR_EMPTY_STR 5

typedef struct BigBool
{
    uint8_t vector[MAX_PARTS];
    size_t num_part;
    size_t num_bit;
} BigBool;


/*
 * Function: int BB_reset(BigBool **BB) 
 * Description: Reset structure.
 
 * Return:
        1) ERR_OK if all work properly
        2) ERR_NULL_ARG if BB == NULL
 */
int BB_reset(BigBool *BB);

/*
 * Function: int BB_reverseBits(BigBool **BB, int startBit, int endBit)
 * Description: Reverse vector.
 
 * Return:
        1) ERR_OK if all work properly,
        2) ERR_NULL_ARG if BB == NULL,
 */
int BB_reverse_bits(BigBool *BB, int startBit, int endBit);

/* 
 * Function: int BB_from_str(char* str , BigBool* res )
 
 * Description: Convert string containing only '1' and '0' to BB vector.
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_NULL_ARG if BB == NULL,
        3) ERR_EMPTY_VECTOR if strlen(str) == 0,
        4) ERR_BAD_STRING if string is not only '1' and '0'.
 */
int BB_from_str(char* str , BigBool* res );

/*
 * Function: int BB_from_uint64(uint64_t num , BigBool* res)
 * Description:  Convert 64 bit number to BB vector.
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_NULL_ARG if res == NULL.
 */

int BB_from_uint64(uint64_t num , BigBool* res);

/*
 * Function: char* BB_to_str(BigBool* res)
 * Description: Convert BB vector to string of '1' and '0'.
 * Returns:
        1) Pointer to string,
        2) NULL, if failed to allocate.
 */
char* BB_to_str(BigBool* res);

/*
 * Function: int BB_disjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
 
 * Description:  makes disjunction of two boolean vectors
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_disjunction (BigBool* BB1, BigBool* BB2, BigBool* res);

/*
 * Function: int BB_conjunction (BigBool* BB1, BigBool* BB2, BigBool* res)
 
 * Description:  makes conjunction of two boolean vectors
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_conjunction (BigBool* BB1, BigBool* BB2, BigBool* res);

/*
 * Function: int BB_xor (BigBool* BB1, BigBool* BB2, BigBool* res)
 * Description:  makes exclusive disjunction of two boolean vectors
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_xor (BigBool* BB1, BigBool* BB2, BigBool* res);

/*
 * Function: int BB_inversion (BigBool* BB1, BigBool* res)
 
 * Description:   makes inversion of bool vector
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL.
 */
int BB_inversion (BigBool* BB1, BigBool* res);

/*
 * Function: int BB_left_shift (BigBool* BB, BigBool* res, size_t len_shift)
 
 * Description:  do left shift of bool vector
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) ERR_BIG_SHIFT if len of shift is bigger than len of vector,
        4) ERR_SMALL_SHIFT if len of shift less than 0.
 */
int BB_left_shift (BigBool* BB, BigBool* res, int len_shift);

/*
 * Function: int BB_right_shift (BigBool* BB, BigBool* res, size_t len_shift)
 
 * Description: do right shift of bool vector
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) ERR_BIG_SHIFT if len of shift is bigger than len of vector,
        4) ERR_SMALL_SHIFT if len of shift less than 0.
 */
int BB_right_shift (BigBool* BB, BigBool* res, int len_shift);

/*
 * Function: int BB_cyclic_left_shift (BigBool* BB, BigBool** res, size_t len_shift)
 
 * Description: do cyclic left shift of bool vector
 
 * Returns:
        1) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) BB_cyclic_right_shift(BB, res, -len_shift) if len of shift less than 0,
 *
 */
int BB_cyclic_left_shift (BigBool* BB, BigBool* res, int len_shift);

/*
 * Function: int BB_cyclic_right_shift (BigBool*BB, BigBool** res, size_t len_shift)
 
 * Description: do cyclic right shift of bool vector
 
 * Returns:
        ) ERR_OK if function work properly,
        2) ERR_BAD_ARG if BB == NULL,
        3) BB_cyclic_left_shift(BB, res, -len_shift) if len of shift less than 0,
 *
 */
int BB_cyclic_right_shift (BigBool*BB, BigBool* res, int len_shift);

#endif //PROGS_LIBRARY_H
