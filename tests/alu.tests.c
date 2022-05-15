#include <assert.h>
#include <stdlib.h>

#include "alu.h"

void test_alu_compute(uint16_t x,
		      uint16_t y,
		      bool zx,
		      bool nx,
		      bool zy,
		      bool ny,
		      bool f,
		      bool no,
		      uint16_t expected_out,
		      bool expected_zr,
		      bool expected_ng
		      );

int main(void)
{
	uint16_t expected_out;
	bool expected_zr, expected_ng;
	// alu control flags
	bool zx, nx, zy, ny, f, no;
	
	/** 0 (constant)
	 * for x: any, for y: any
	 * always return 0
	 * zr: set
	 * ng: unset
	 */
	zx = 1; nx = 0; zy = 1; ny = 0; f = 1; no = 0;
	expected_out = 0;
	expected_zr = 1;
	expected_ng = 0;
	test_alu_compute(88, 282, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** 1 (constant)
	 * for x: any, for y: any
	 * always return 1
	 * zr: unset
	 * ng: unset
	 */
	zx = 1; nx = 1; zy = 1; ny = 1; f = 1; no = 1;
	expected_out = 1;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** -1 (0xFFFF, constant)
	 * for x: any, for y: any
	 * always return -1 (0xFFFF)
	 * zr: unset
	 * ng: set
	 */
	zx = 1; nx = 1; zy = 1; ny = 0; f = 1; no = 0;
	expected_out = 0xFFFF;
	expected_zr = 0;
	expected_ng = 1;
	test_alu_compute(0, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x
	 * for x: 42, for y: 0
	 * return x
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 1; ny = 1; f = 0; no = 0;
	expected_out = 42;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(42, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** y
	 * for x: 0, for y: 0x8401
	 * return y
	 * zr: unset
	 * ng: set
	 */
	zx = 1; nx = 1; zy = 0; ny = 0; f = 0; no = 0;
	expected_out = 0x8401;
	expected_zr = 0;
	expected_ng = 1;
	test_alu_compute(0, 0x8401, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** ~x (bitwise)
	 * for x: 0x84E1, for y: 0
	 * return ~x (bitwise) 
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 1; ny = 1; f = 0; no = 1;
	expected_out = 0x7B1E;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0x84E1, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** ~y (bitwise)
	 * for x: 0, for y: 0x7B1E
	 * return ~y (bitwise) 
	 * zr: unset
	 * ng: set
	 */
	zx = 1; nx = 1; zy = 0; ny = 0; f = 0; no = 1;
	expected_out = 0x84E1;
	expected_zr = 0;
	expected_ng = 1;
	test_alu_compute(0, 0x7B1E, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** -x (two's compliment)
	 * for x: 0x8003, for y: 0
	 * return -x (two's compliment negation)
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 1; ny = 1; f = 1; no = 1;
	expected_out = 0x7FFD;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0x8003, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** -y (two's compliment)
	 * for x: 0, for y: 0
	 * return -y (two's compliment negation)
	 * zr: set
	 * ng: unset
	 */
	zx = 1; nx = 1; zy = 0; ny = 0; f = 1; no = 1;
	expected_out = 0;
	expected_zr = 1;
	expected_ng = 0;
	test_alu_compute(0, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x+1
	 * for x: 0, for y: 0
	 * return x+1
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 1; zy = 1; ny = 1; f = 1; no = 1;
	expected_out = 1;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** y+1
	 * for x: 0, for y: 0xFFFF
	 * return y+1 (demonstrates overflow characteristics [wrap around])
	 * zr: set
	 * ng: unset
	 */
	zx = 1; nx = 1; zy = 0; ny = 1; f = 1; no = 1;
	expected_out = 0;
	expected_zr = 1;
	expected_ng = 0;
	test_alu_compute(0, 0xFFFF, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x-1
	 * for x: 1, for y: 0
	 * return x-1
	 * zr: set
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 1; ny = 1; f = 1; no = 0;
	expected_out = 0;
	expected_zr = 1;
	expected_ng = 0;
	test_alu_compute(1, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** y-1
	 * for x: 0, for y: 0
	 * return y-1 (demonstrates overflow characteristics [wrap around])
	 * zr: unset
	 * ng: set
	 */
	zx = 1; nx = 1; zy = 0; ny = 0; f = 1; no = 0;
	expected_out = 0xFFFF;
	expected_zr = 0;
	expected_ng = 1;
	test_alu_compute(0, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x+y
	 * for x: 0xFEFF, for y: 0xFEFF
	 * return x+y (overflow wraps around)
	 * zr: unset
	 * ng: set
	 */
	zx = 0; nx = 0; zy = 0; ny = 0; f = 1; no = 0;
	expected_out = 0xFDFE;
	expected_zr = 0;
	expected_ng = 1;
	test_alu_compute(0xFEFF, 0xFEFF, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x-y
	 * for x: 0, for y: 0xFEFF
	 * return x-y (overflow wraps around)
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 1; zy = 0; ny = 0; f = 1; no = 1;
	expected_out = 0x101;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0, 0xFEFF, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** y-x
	 * for x: 0xFEFF, for y: 0
	 * return y-x (overflow wraps around)
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 0; ny = 1; f = 1; no = 1;
	expected_out = 0x101;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0xFEFF, 0, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x&y
	 * for x: 0xFEFF, for y: 0x7 
	 * return x&y (overflow wraps around)
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 0; zy = 0; ny = 0; f = 0; no = 0;
	expected_out = 0x7;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0xFEFF, 0x7, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	/** x|y
	 * for x: 0x04A6, for y: 0x4443
	 * return x&y
	 * zr: unset
	 * ng: unset
	 */
	zx = 0; nx = 1; zy = 0; ny = 1; f = 0; no = 1;
	expected_out = 0x44E7;
	expected_zr = 0;
	expected_ng = 0;
	test_alu_compute(0x04A6, 0x4443, zx, nx, zy, ny, f, no, expected_out, expected_zr, expected_ng);

	exit(0);
}

void test_alu_compute(uint16_t x,
		      uint16_t y,
		      bool zx,
		      bool nx,
		      bool zy,
		      bool ny,
		      bool f,
		      bool no,
		      uint16_t expected_out,
		      bool expected_zr,
		      bool expected_ng
		      )
{
	uint16_t out;
	bool zr, ng;

	alu_compute(x, y, zx, nx, zy, ny, f, no, &out, &zr, &ng);

	assert(out == expected_out);
	assert(zr == expected_zr);
	assert(ng == expected_ng);
}
