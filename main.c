#include"fractol.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define IMG_WIDTH 800
# define IMG_HEIGHT 800

#define X_EVENT_KEY_PRESS		4


void draw(t_options *options)
{

	int		count_w;
	int		count_h;
	int		result;
	t_complex c;
	count_h = 0;
	while (++count_h < IMG_HEIGHT)
	{
		c.im = options->h_lo + count_h * ((double)(options->h_up - options->h_lo)/IMG_HEIGHT);
		count_w = 0;
		while (++count_w < IMG_WIDTH)
		{
			c.re = options->v_lo + count_w * ((double)(options->v_up - options->v_lo)/IMG_WIDTH);
			result = julia(c, options);
			if (result)
			{
				options->img->data[count_h * IMG_WIDTH + count_w] = ((result * (16777215/100))%777215)<<options->shiftColor;
			}
			else
				options->img->data[count_h * IMG_WIDTH + count_w] = 0x000000;
		}
	}
	mlx_put_image_to_window(options->mlx->mlx_ptr, options->mlx->win, options->img->img_ptr, 0, 0);
}

int				key_press(int keycode, t_options *options)
{
	double	h_transaction;
	double	v_transaction;

	h_transaction = (options->h_up - options->h_lo)*0.2;
	v_transaction = (options->v_up - options->v_lo)*0.2;
	if (keycode == 2 || keycode == 124)
	{
		options->v_lo += v_transaction;
		options->v_up += v_transaction;
		draw(options);
	}
	else if (keycode == 0 || keycode == 123)
	{
		options->v_lo -= v_transaction;
		options->v_up -= v_transaction;
		draw(options);
	}
	else if (keycode == 1|| keycode == 125)
	{
		options->h_lo += h_transaction;
		options->h_up += h_transaction;
		draw(options);
	}
	else if (keycode == 13|| keycode == 126)
	{
		options->h_lo -= h_transaction;
		options->h_up -= h_transaction;
		draw(options);
	}
	else if (keycode == 8)
	{
		options->shiftColor = (options->shiftColor + 1) % 8;
		draw(options);
	}
	else if (keycode == 6 && options->iterations < 200)
	{
		options->iterations += 10;
		draw(options);
	}
	else if (keycode == 45 && options->iterations > 50)
	{
		options->iterations -= 10;
		draw(options);
	}
	else if (keycode == 53) 
		exit(0);
	return (0);
}

int	close_program(int keycode, int x, int y, t_options *options)
{
	exit(0);
}

int	mouse_action(int keycode,int x, int y, t_options *options)
{
	t_complex	c;
	x-=400;
	y-=400;
	double	v_transaction;
	double	h_transaction;
	// zoom
	if (keycode == 1)
	{
		v_transaction = (options->v_up - options->v_lo)/IMG_WIDTH;
		h_transaction = (options->h_up - options->h_lo)/IMG_HEIGHT;
		c.im = x * v_transaction;
		c.re = x * h_transaction;
		options->c = c;
		draw(options);
	}
	if (keycode == 5)
	{
		v_transaction = (options->v_up - options->v_lo)/IMG_WIDTH;
		h_transaction = (options->h_up - options->h_lo)/IMG_HEIGHT;

		options->v_lo += x * v_transaction;
		options->v_up += x * v_transaction;
		options->h_lo += y * h_transaction;
		options->h_up += y * h_transaction;

		v_transaction = (options->v_up - options->v_lo)*0.1;
		h_transaction = (options->h_up - options->h_lo)*0.1;
		options->v_lo -= v_transaction;
		options->v_up += v_transaction;
		options->h_lo -= h_transaction;
		options->h_up += h_transaction;

		v_transaction = (options->v_up - options->v_lo)/IMG_WIDTH;
		h_transaction = (options->h_up - options->h_lo)/IMG_HEIGHT;
		options->v_lo -= x * v_transaction;
		options->v_up -= x * v_transaction;
		options->h_lo -= y * h_transaction;
		options->h_up -= y * h_transaction;
		draw(options);
	}
	else if (keycode == 4)
	{

		v_transaction = (options->v_up - options->v_lo)/IMG_WIDTH;
		h_transaction = (options->h_up - options->h_lo)/IMG_HEIGHT;
		
		options->v_lo += x * v_transaction;
		options->v_up += x * v_transaction;
		options->h_lo += y * h_transaction;
		options->h_up += y * h_transaction;

		v_transaction = (options->v_up - options->v_lo)*0.1;
		h_transaction = (options->h_up - options->h_lo)*0.1;
		options->v_lo += v_transaction;
		options->v_up -= v_transaction;
		options->h_lo += h_transaction;
		options->h_up -= h_transaction;

		v_transaction = (options->v_up - options->v_lo)/IMG_WIDTH;
		h_transaction = (options->h_up - options->h_lo)/IMG_HEIGHT;

		options->v_lo -= x * v_transaction;
		options->v_up -= x * v_transaction;
		options->h_lo -= y * h_transaction;
		options->h_up -= y * h_transaction;

		draw(options);
	}
	return (0);
}

int	main(void)
{
	t_mlx	*mlx;
	t_img	img;
	t_options	options;
	options.h_lo = -2;
	options.h_up = 2;
	options.v_lo = -2;
	options.v_up = 2;
	options.shiftColor = 0;
	options.iterations = 50;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fract-ol");
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	options.img = &img;
	options.mlx = mlx;
	draw(&options);
	mlx_hook(mlx->win,2, 1L << 0,&key_press, &options);
	mlx_hook(mlx->win,4, 1L << 0,&mouse_action, &options);
	mlx_hook(mlx->win,17, 1L << 0,&close_program, &options);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
