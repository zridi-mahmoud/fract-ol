#include"../fractol.h"

int julia(t_complex z,t_options *options)
{
	int		iterations;
	t_complex	c;
	c = options->c;

	iterations = options->iterations;
	while(iterations && z.im * z.im + z.re * z.re <= 4)
	{
		z = complex_add(complex_mul(z,z),c);
		iterations--;
	}
	return (iterations);
}
