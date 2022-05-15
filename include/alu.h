#ifndef ALU_H
#define ALU_H

#include <stdbool.h>
#include <stdint.h>

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
		);

uint16_t if_add_el_and(uint16_t x, uint16_t y, bool f);
uint16_t if_negate(uint16_t x, bool nx);
uint16_t if_zero(uint16_t x, bool zx);

bool is_ng(uint16_t x);
bool is_zr(uint16_t x);

#endif
