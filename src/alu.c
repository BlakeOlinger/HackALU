
#include "alu.h"

void alu_compute(uint16_t x,
		 uint16_t y,
		 bool zx,
		 bool nx,
		 bool zy,
		 bool ny,
		 bool f,
		 bool no,
		 uint16_t *out,
		 bool *zr,
		 bool *ng
		)
{
	x = if_zero(x, zx);
	x = if_negate(x, nx);

	y = if_zero(y, zy);
	y = if_negate(y, ny);

	*out = if_add_el_and(x, y, f);
	*out = if_negate(*out, no);

	*zr = is_zr(*out);

	*ng = is_ng(*out);
}

uint16_t if_add_el_and(uint16_t x, uint16_t y, bool f)
{
	return f ? ((x + y) & 0xFFFF) : x & y;
}

uint16_t if_negate(uint16_t x, bool nx)
{
	return nx ? ~x : x;
}

uint16_t if_zero(uint16_t x, bool z)
{
	return z ? 0 : x;
}

bool is_ng(uint16_t x)
{
	return (x & 0x8000) == 0x8000;
}

bool is_zr(uint16_t x)
{
	return x == 0;
}
