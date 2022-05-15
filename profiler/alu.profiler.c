#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "alu.h"

void fpcsv(FILE *fd, unsigned long op_result);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: <num_seconds>\n");
		exit(0);
	}

	int num_secs = atoi(argv[1]);

	puts("Running profiler...\n");
	printf("Run length: %s (seconds)\n\n", argv[1]);

	uint16_t out = 0;
	bool zr, ng;
	unsigned long op_zero		= 0,
		      op_one  		= 0,
		      op_neg_one	= 0,
		      op_x		= 0,
		      op_y		= 0,
		      op_bang_x		= 0,
		      op_bang_y		= 0,
		      op_neg_x		= 0,
		      op_neg_y		= 0,
		      op_x_p_one	= 0,
		      op_y_p_one	= 0,
		      op_x_s_one	= 0,
		      op_y_s_one	= 0,
		      op_x_p_y		= 0,
		      op_x_s_y		= 0,
		      op_y_s_x		= 0,
		      op_x_and_y	= 0,
		      op_x_or_y		= 0;

	clock_t begin = clock();
	clock_t current = clock();

	int i = 0;
	while ((current - begin) / CLOCKS_PER_SEC < num_secs)
	{
		switch (i)
		{
			case 0:
				alu_compute(i, i, 1, 0, 1, 0, 1, 0, &out, &zr, &ng);
				++op_zero;
			break;

			case 1:
				alu_compute(i, i, 1, 1, 1, 1, 1, 1, &out, &zr, &ng);
				++op_one;
			break;

			case 2:
				alu_compute(i, i, 1, 1, 1, 0, 1, 0, &out, &zr, &ng);
				++op_neg_one;
			break;

			case 3:
				alu_compute(i, i, 0, 0, 1, 1, 0, 0, &out, &zr, &ng);
				++op_x;
			break;

			case 4:
				alu_compute(i, i, 1, 1, 0, 0, 0, 0, &out, &zr, &ng);
				++op_y;
			break;

			case 5:
				alu_compute(i, i, 0, 0, 1, 1, 0, 1, &out, &zr, &ng);
				++op_bang_x;
			break;
			
			case 6:
				alu_compute(i, i, 1, 1, 0, 0, 0, 1, &out, &zr, &ng);
				++op_bang_y;
			break;

			case 7:
				alu_compute(i, i, 0, 0, 1, 1, 1, 1, &out, &zr, &ng);
				++op_neg_x;
			break;

			case 8:
				alu_compute(i, i, 1, 1, 0, 0, 1, 1, &out, &zr, &ng);
				++op_neg_y;
			break;

			case 9:
				alu_compute(i, i, 0, 1, 1, 1, 1, 1, &out, &zr, &ng);
				++op_x_p_one;
			break;

			case 10:
				alu_compute(i, i, 1, 1, 0, 1, 1, 1, &out, &zr, &ng);
				++op_y_p_one;
			break;

			case 11:
				alu_compute(i, i, 0, 0, 1, 1, 1, 0, &out, &zr, &ng);
				++op_x_s_one;
			break;

			case 12:
				alu_compute(i, i, 1, 1, 0, 0, 1, 0, &out, &zr, &ng);
				++op_y_s_one;
			break;

			case 13:
				alu_compute(i, i, 0, 0, 0, 0, 1, 0, &out, &zr, &ng);
				++op_x_p_y;
			break;

			case 14:
				alu_compute(i, i, 0, 1, 0, 0, 1, 1, &out, &zr, &ng);
				++op_x_s_y;
			break;

			case 15:
				alu_compute(i, i, 0, 0, 0, 1, 1, 1, &out, &zr, &ng);
				++op_y_s_x;
			break;

			case 16:
				alu_compute(i, i, 0, 0, 0, 0, 0, 0, &out, &zr, &ng);
				++op_x_and_y;
			break;

			case 17:
				alu_compute(i, i, 0, 1, 0, 1, 0, 1, &out, &zr, &ng);
				++op_x_or_y;
			break;
		}

		++i;
		i %= 18;

		current = clock();
	}

	FILE *ofile = fopen("profiler/profiler.output.dat", "w");
	assert(ofile != NULL);

	fprintf(ofile, "0,1,-1,x,y,!x,!y,-x,-y,x+1,y+1,x-1,y-1,x+y,x-y,y-x,x&y,x|y,\n");

	fpcsv(ofile, op_zero);
	fpcsv(ofile, op_one);
	fpcsv(ofile, op_neg_one);
	fpcsv(ofile, op_x);
	fpcsv(ofile, op_y);
	fpcsv(ofile, op_bang_x);
	fpcsv(ofile, op_bang_y);
	fpcsv(ofile, op_neg_x);
	fpcsv(ofile, op_neg_y);
	fpcsv(ofile, op_x_p_one);
	fpcsv(ofile, op_y_p_one);
	fpcsv(ofile, op_x_s_one);
	fpcsv(ofile, op_y_s_one);
	fpcsv(ofile, op_x_p_y);
	fpcsv(ofile, op_x_s_y);
	fpcsv(ofile, op_y_s_x);
	fpcsv(ofile, op_x_and_y);
	fpcsv(ofile, op_x_or_y);

	fputc('\n', ofile);
	
	fclose(ofile);

	puts("Profiler complete.\n");
	puts("Output as csv in: profiler/profiler.output.dat");
	exit(0);
}

void fpcsv(FILE *fd, unsigned long op_result)
{
	fprintf(fd, "%lu,", op_result);
}
