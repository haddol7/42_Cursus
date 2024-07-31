#include "print.h"
#include "utils.h"

void write_color(t_color3 pixel_color)
{
	// printf("%d %d %d\n", (int)clamp((int)(255.999 * pixel_color.x), 0, 255.999),\
	// 					 (int)clamp((int)(255.999 * pixel_color.y), 0, 255.999),\
	// 				 	 (int)clamp((int)(255.999 * pixel_color.z), 0, 255.999));

	printf("%d %d %d\n", (int)(255.999 * pixel_color.x / 100),\
						 (int)(255.999 * pixel_color.y / 100),\
					 	 (int)(255.999 * pixel_color.z / 100));
}
