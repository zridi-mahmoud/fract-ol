#ifndef FRACTOL_H
# define FRACTOL_H
# include<stdlib.h>
# include"mlx.h"

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
}				t_mlx;

typedef struct s_complex
{
	float	im;
	float	re;
}	t_complex;

typedef struct s_options
{
	float	h_lo;
	float h_up;
	float	v_lo;
	float v_up;
	int r;
	int	g;
	int	b;
	t_img	*img;
	t_mlx	*mlx;
	int	shiftColor;
	int	iterations;
	t_complex	c;

}	t_options;

t_complex	complex_mul(t_complex c, t_complex s);
t_complex	complex_add(t_complex c, t_complex s);
int burning_ship(t_complex c,t_options *options);

#endif