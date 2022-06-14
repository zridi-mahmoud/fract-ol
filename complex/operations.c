#include "fractol.h"

t_complex	complex_mul(t_complex c, t_complex s)
{
	t_complex res;

	res.re = c.re * s.re - c.im * s.im;
	res.im = c.re * s.im + c.im * s.re;
	return (res);
}

t_complex	complex_add(t_complex c, t_complex s)
{
	t_complex res;

	res.re = c.re + s.re;
	res.im = c.im + s.im;
	return (res);
}