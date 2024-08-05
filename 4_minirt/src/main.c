#include <stdio.h>
#include "structures.h"
#include "print.h"
#include "utils.h"

#include "scene.h"
#include "trace.h"

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        exit(12);
    scene->canvas = canvas(WINDOW_W, WINDOW_H);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1)));
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1,1,1), ka);
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

int     main(void)
{
    t_scene     *scene;
	t_mlx		*engine;

	engine = engine_init();
    scene = scene_init();
	draw_ray(scene, engine);
	mlx_loop(engine->mlx);
    return (0);
}
