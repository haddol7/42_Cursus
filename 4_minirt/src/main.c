#include <stdio.h>
#include "engine.h"
#include "structures.h"
#include "print.h"
#include "utils.h"

#include "scene.h"
#include "trace.h"
#include "map.h"

t_scene *scene_init(int fd)
{
    t_scene     *scene;
    // t_object    *world;
    // t_object    *lights;
    // double      ka;


// world 부터 하나씩 유효성 검사하면서 추가, -> 에러 났을 때 exit
// 맵 스케일 이미지 검증
// ㄴㅋ포ㅟㅐㅇ고 타.ㅋ로
    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        exit(12);
	map_validity(fd, scene);
    // scene->canvas = canvas(WINDOW_W, WINDOW_H);
    // scene->camera = camera(&scene->canvas, point3(0, 0, 10));
    // world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
    // oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1)));
    // oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
    // scene->world = world;
    // lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
    // scene->light = lights;
    // ka = 0.1;
    // scene->ambient = vmult(color3(1,1,1), ka);
    return (scene);
}

t_mlx	*engine_init(void)
{
	t_mlx	*engine;

	engine = (t_mlx *)malloc(sizeof(t_mlx));
	engine->img = (t_img *)malloc(sizeof(t_img));
	if (engine == NULL)
		exit(ERR_MLC);
	engine->mlx = mlx_init();
	if (engine->mlx == NULL)
		exit(ERR_MLX);
	engine->win = mlx_new_window(engine->mlx, WINDOW_W, WINDOW_H, "minirt");
	if (engine->win == NULL)
		exit(ERR_MLX);
	engine->img->id = mlx_new_image(engine->mlx, WINDOW_W, WINDOW_H);
	if (engine->img->id == NULL)
		exit(ERR_MLX);
	engine->img->addr = mlx_get_data_addr(engine->img->id, &engine->img->bits_per_pixel, \
										&engine->img->line_size, &engine->img->endian);
	return (engine);
}

void	draw_ray(t_scene *scene, t_mlx *engine)
{
	int         i;
    int         j;
    double      u;
    double      v;
    t_color3    pixel_color;

	j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {	
			pixel_color = vec3(0, 0, 0);
			for (int sample = 0; sample < scene->camera.samples_per_pixel; sample++)
			{	
            	if (scene->camera.samples_per_pixel > 1)
				{
					u = ((double)i + random_double_(-1, 1)) / (scene->canvas.width - 1);
            		v = ((double)j + random_double_(-1, 1)) / (scene->canvas.height - 1);
				}
				else
				{
					u = ((double)i) / (scene->canvas.width - 1);
            		v = ((double)j) / (scene->canvas.height - 1);
				}
            	scene->ray = ray_primary(&scene->camera, u, v);
            	pixel_color = ray_color(scene, pixel_color);
			}
            write_color(engine->img, pixel_color, i, scene->canvas.height - 1 - j);
            ++i;
        }
        --j;
    }
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->id, 0, 0);
}

int	terminate(void *data_addr)
{
	t_data	*data;

	data = (t_data *)data_addr;
	mlx_destroy_image(data->engine->mlx, data->engine->img->id);
	mlx_destroy_window(data->engine->mlx, data->engine->win);
	printf("\033[0;92mProgram closed!\n");
	exit(0);
}

int	key_hook(int keycode, void *data_addr)
{	
	t_data	*data;
	t_sphere *sp;

	data = (t_data *)data_addr;
	sp = (t_sphere *)data->scene->world->element;
	if (keycode == KEY_A)
		sp->center = vplus_(sp->center, 0.1, 0, 0);
	else if (keycode == KEY_D)
		sp->center = vplus_(sp->center, -0.1, 0, 0);
	// else if (keycode == KEY_W)
	// 	data->map.angular.x -= 5;
	// else if (keycode == KEY_S)
	// 	data->map.angular.x += 5;
	// else if (keycode == KEY_Q)
	// 	data->map.angular.y -= 5;
	// else if (keycode == KEY_E)
	// 	data->map.angular.y += 5;
	// else if (keycode == KEY_C)
	// 	center_map(data);
	else if (keycode == KEY_ESC)
		terminate((void *)data);
	draw_ray(data->scene, data->engine);
	return (0);
}

int     main(int argc, char *argv[])
{	
	int			fd;
	t_data		data;

	data.engine = engine_init();
	fd = argument_validity(argc, argv[1]);
   	data.scene = scene_init(fd);
	// draw_ray(data.scene, data.engine);
	// mlx_hook(data.engine->win, 2, 0, key_hook, &data);
	// //mlx_hook(data.engine->win, 4, 0, mouse_press_hook, &data);
	// //mlx_hook(data.engine->win, 5, 0, mouse_release_hook, &data);
	// //mlx_hook(data.engine->win, 6, 0, mouse_drag_hook, &data);
	// mlx_hook(data.engine->win, 17, 0, terminate, &data);
	// mlx_loop(data.engine->mlx);
    return (0);
}
