  /****h* tools/strcalc
 *
 * NAME
 *   strcalc -- calculations using strings
 *   Provides basic mathematical operations on values represented as strings
 *
 * AUTHORS
 *   Matthias Heil
 *
 * DESCRIPTION
 *    The module uses a string to represent values, and provides operations
 *   to perform calculations with these values.
 *    Results are stored in an internal buffer, so you have to make a copy
 *   of them if you need to store the result.
 *
 ******/

#ifndef _STRCALC_H_
#define _STRCALC_H_

#define BIGGEST_INTEGER_SIZE_IN_BYTES 8
#define SCDEBUG

/*****************************************************************************
 * typedefs, enums and structs
 *****************************************************************************/
enum {
  SC_0 = 0,
  SC_1,
  SC_2,
  SC_3,
  SC_4,
  SC_5,
  SC_6,
  SC_7,
  SC_8,
  SC_9,
  SC_A,
  SC_B,
  SC_C,
  SC_D,
  SC_E,
  SC_F,
};

/**
 * Possible operations on integer values.
 */
enum {
  SC_ADD = 0,		/**< Addition */
  SC_SUB,		/**< Substraction */
  SC_NEG,		/**< Unary Minus */
  SC_MUL,		/**< Multiplication */
  SC_DIV,		/**< Integer Division (with rounding toward zero ?) */
  SC_MOD,		/**< Devision Remainder */
  SC_SHL,		/**< Left Shift */
  SC_SHR,		/**< Logical (unsigned) Right Shift */
  SC_SHRS,		/**< Arithmetic (signed) Right Shift */
  SC_ROT,		/**< Rotation (both directions) */
  SC_AND,		/**< Bitwise And */
  SC_OR,		/**< Bitwise Or */
  SC_NOT,		/**< Bitwise Not */
  SC_XOR,		/**< Bitwise Exclusive Or */
};

/**
 * The output mode for ntger values.
 */
enum base_t {
  SC_HEX,	/**< hexadecimal output */
  SC_DEC,	/**< decimal output */
  SC_OCT,	/**< octal output */
  SC_BIN,	/**< binary output */
};

/*
 * definitions and macros
 */
#define sc_add(a, b) sc_calc((a), (b), SC_ADD)
#define sc_sub(a, b) sc_calc((a), (b), SC_SUB)
#define sc_neg(a) sc_calc((a), NULL, SC_NEG)
#define sc_and(a, b) sc_calc((a), (b), SC_AND)
#define sc_or(a, b) sc_calc((a), (b), SC_OR)
#define sc_xor(a, b) sc_calc((a), (b), SC_XOR)
#define sc_not(a) sc_calc((a), NULL, SC_NOT)
#define sc_mul(a, b) sc_calc((a), (b), SC_MUL)
#define sc_div(a, b) sc_calc((a), (b), SC_DIV)
#define sc_mod(a, b) sc_calc((a), (b), SC_MOD)
#define sc_shl(a, b, c, d) sc_bitcalc((a), (b), (c), (d), SC_SHL)
#define sc_shr(a, b, c, d) sc_bitcalc((a), (b), (c), (d), SC_SHR)
#define sc_shrs(a, b, c, d) sc_bitcalc((a), (b), (c), (d), SC_SHRS)
#define sc_rot(a, b, c, d) sc_bitcalc((a), (b), (c), (d), SC_ROT)

/*
 * function declarations
 */
const void *sc_get_buffer(void);
const int sc_get_buffer_length(void);

void sc_val_from_str(const char *str, unsigned int len);
void sc_val_from_long(long l);
long sc_val_to_long(const void *val);
void sc_min_from_bits(unsigned int num_bits, unsigned int sign);
void sc_max_from_bits(unsigned int num_bits, unsigned int sign);

void sc_calc(const void *val1, const void *val2, unsigned op);
void sc_bitcalc(const void *val1, const void *val2, unsigned radius, unsigned sign, unsigned op);
int  sc_comp(const void *val1, const void *val2);

unsigned char sc_sub_bits(const void *val, int len, unsigned byte_ofs);

/**
 * Converts a tarval into a string.
 *
 * @param val1		the value pointer
 * @param bits		number of valid bits in this value
 * @param base		output base
 */
const char *sc_print(const void *val1, unsigned bits, enum base_t base);

#endif /* _STRCALC_H_ */
