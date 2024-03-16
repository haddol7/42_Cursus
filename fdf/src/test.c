#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

#define SIZEX 500
#define SIZEY 500

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_param
{
	int 	x;
	int 	y;
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
} t_param;

int key_press(int keycode, t_param *param)
{
	if (keycode == KEY_A)
		param->x -= 20;
	else if (keycode == KEY_D)
		param->x += 20;
	else if (keycode == KEY_W)
		param->y -= 20;
	else if (keycode == KEY_S)
		param->y += 20;

	if (param->x < 0)
		param->x = 0;
	if (param->y < 0)
		param->y = 0;
	mlx_clear_window(param->mlx, param->mlx_win);
	mlx_put_image_to_window(param->mlx, param->mlx_win, param->img->img, param->x, param->y);
	return (0);
}

void my_pixel_put(t_data *img, int x, int y, int color)
{
	void	*img_addr;

	img_addr = img->addr + img->bits_per_pixel / 8 * x + img->line_length * y;
	*(int *)img_addr = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_param	param;

	param.x = 0;
	param.y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	param.img = &img;
	param.mlx = mlx;
	param.mlx_win = mlx_win;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < i; j++)
			my_pixel_put(&img, j, i, 0xffffff);
	}

	mlx_hook(mlx_win, 2, 0, key_press, &param);
	mlx_loop(mlx);
}
