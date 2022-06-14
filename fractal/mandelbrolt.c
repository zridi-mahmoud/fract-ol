#include "fractol.h"

int mandelbrolt(t_complex c,t_options *options)
{
	int		iterations;
	t_complex	z;
	t_complex	z2;
	z.im = 0;
	z.re = 0;
	z2.im = 0;
	z2.re = 0;

	iterations = options->iterations;
	while(iterations && z.im * z.im + z.re * z.re <= 4)
	{
		z = complex_add(complex_add(complex_mul(z,z),c),z2);
		iterations--;
	}
	return (iterations);
}