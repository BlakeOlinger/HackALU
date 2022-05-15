#include <assert.h>
#include <stdlib.h>

#include "alu.h"

int main(void)
{
	/**
	 * set f flag returns x + y
	 */
	assert(if_add_el_and(38, 10, true) == 48);

	/**
	 * x + y overflows as expected for 16 bit sized ints
	 */
	assert(if_add_el_and(0xFEFF, 0xFEFF, true) == 0xFDFE);

	/**
	 * unset f flag return bitwise x & y
	 */
	assert(if_add_el_and(13, 851, false) == 1);

	/**
	 * setting negate x performs a bit-wise negation of x (one's compliment)
	 */
	assert(if_negate(72, true) == 0xFFB7);

	/**
	 * unset negate x returns x
	 */
	assert(if_negate(1029, false) == 1029);

	/**
	 * setting zero input flag returns zero
	 */
	assert(if_zero(25, true) == 0);

	/**
	 * unset zero input flag returns x
	 */
	assert(if_zero(888, false) == 888);

	/**
	 * return true if negative (msb of 16 bit int is set)
	 */
	assert(is_ng(0x8440) == true);

	/**
	 * return false if not negative (msb of 16 bit int not set)
	 */
	assert(is_ng(0x7FFF) == false);

	/**
	 * return true if x is zero
	 */
	assert(is_zr(0) == true);

	/**
	 * return false if x is not zero
	 */
	assert(is_zr(80) == false);

	exit(0);
}
