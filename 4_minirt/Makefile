NAME := minirt

CC := cc
CFLAGS := -Wall -Wextra -Werror

LIB := lib/
LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a

MLX_DIR := $(LIB)mlx/
MLX := $(MLX_DIR)libmlx.dylib
MLXFLAGS := -L$(MLX_DIR) -framework OpenGL -framework AppKit

HEADER  := -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS_ENGINE =	src/engine/key_hook.c \
				src/engine/key_hook_object.c \
				src/engine/key_hook_object_2.c \
				src/engine/key_hook_object_3.c \
				src/engine/mouse_hook.c

SRCS_PRINT =	src/print/print.c \
				src/print/print_image.c

SRCS_SCENE =	src/scene/canvas.c \
				src/scene/object_create.c \
				src/scene/object_utils.c

SRCS_TRACE =	src/trace/hit/hit_sphere.c \
				src/trace/hit/hit_cylinder.c \
				src/trace/hit/hit_plane.c \
				src/trace/hit/hit_cone.c \
				src/trace/hit/hit.c \
				src/trace/hit/normal.c \
				src/trace/ray/phong_lighting.c \
				src/trace/ray/ray.c \
				src/trace/texture/uv_mapping.c \
				src/trace/texture/uv_axis_mapping.c \
				src/trace/texture/texture.c

SRCS_UTILS = 	src/utils/vector/vector.c\
				src/utils/vector/vector_2.c\
				src/utils/vector/vector_3.c\
				src/utils/vector/vector_4.c\
				src/utils/objects_utils.c \
				src/utils/utils.c

SRCS_MAP = 		src/parsing/validity.c \
				src/parsing/atof.c \
				src/parsing/element.c \
				src/parsing/element_capital.c \
				src/parsing/element_utils.c \
				src/parsing/element_utils_2.c

SRCS_ENGINE =	src/engine/key_hook.c \
				src/engine/key_hook_object.c \
				src/engine/key_hook_object_2.c \
				src/engine/key_hook_object_3.c \
				src/engine/mouse_hook.c

SRC_MAN =		$(SRCS_ENGINE) \
				$(SRCS_PRINT) \
				$(SRCS_SCENE) \
				$(SRCS_TRACE) \
				$(SRCS_UTILS) \
				$(SRCS_MAP) \
				src/main.c

BONUS_ENGINE =	bonus/src/engine/key_hook_bonus.c \
				bonus/src/engine/key_hook_object_bonus.c \
				bonus/src/engine/key_hook_object_2_bonus.c \
				bonus/src/engine/key_hook_object_3_bonus.c \
				bonus/src/engine/mouse_hook_bonus.c

BONUS_PRINT =	bonus/src/print/print_bonus.c \
				bonus/src/print/print_image_bonus.c

BONUS_SCENE =	bonus/src/scene/canvas_bonus.c \
				bonus/src/scene/object_create_bonus.c \
				bonus/src/scene/object_utils_bonus.c

BONUS_TRACE =	bonus/src/trace/hit/hit_sphere_bonus.c \
				bonus/src/trace/hit/hit_cylinder_bonus.c \
				bonus/src/trace/hit/hit_plane_bonus.c \
				bonus/src/trace/hit/hit_cone_bonus.c \
				bonus/src/trace/hit/hit_bonus.c \
				bonus/src/trace/hit/normal_bonus.c \
				bonus/src/trace/ray/phong_lighting_bonus.c \
				bonus/src/trace/ray/ray_bonus.c \
				bonus/src/trace/texture/uv_mapping_bonus.c \
				bonus/src/trace/texture/uv_axis_mapping_bonus.c \
				bonus/src/trace/texture/texture_bonus.c

BONUS_UTILS = 	bonus/src/utils/vector/vector_bonus.c\
				bonus/src/utils/vector/vector_2_bonus.c\
				bonus/src/utils/vector/vector_3_bonus.c\
				bonus/src/utils/vector/vector_4_bonus.c\
				bonus/src/utils/objects_utils_bonus.c \
				bonus/src/utils/utils_bonus.c

BONUS_MAP = 	bonus/src/parsing/validity_bonus.c \
				bonus/src/parsing/atof_bonus.c \
				bonus/src/parsing/element_bonus.c \
				bonus/src/parsing/element_capital_bonus.c \
				bonus/src/parsing/element_utils_bonus.c \
				bonus/src/parsing/element_utils_2_bonus.c

BONUS_ENGINE =	bonus/src/engine/key_hook_bonus.c \
				bonus/src/engine/key_hook_object_bonus.c \
				bonus/src/engine/key_hook_object_2_bonus.c \
				bonus/src/engine/key_hook_object_3_bonus.c \
				bonus/src/engine/mouse_hook_bonus.c

SRC_BONUS =		$(BONUS_ENGINE) \
				$(BONUS_PRINT) \
				$(BONUS_SCENE) \
				$(BONUS_TRACE) \
				$(BONUS_UTILS) \
				$(BONUS_MAP) \
				bonus/src/main_bonus.c

GREEN = \033[0;92m
BLUE = \033[0;94m
WHITE = \033[0;97m
PURPLE = \033[1;35m

ifdef WITH_BONUS
	SRC_FIN = $(SRC_BONUS)
	INC_FLAG = -Ibonus/inc
else
	SRC_FIN = $(SRC_MAN)
	INC_FLAG = -Iinc
endif

OBJS = $(SRC_FIN:.c=.o)
DEPS = $(SRC_FIN:.c=.d)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(HEADER) $(INC_FLAG)

all: 
	@$(MAKE) -C $(MLX_DIR)
	@install_name_tool -id lib/mlx/libmlx.dylib lib/mlx/libmlx.dylib
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) $(NAME)

bonus:
	@$(MAKE) WITH_BONUS=1

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(MLX) $(MLXFLAGS) -o $@

ifdef WITH_BONUS
	@echo "$(PURPLE)🌏 minirt : make bonus done!$(WHITE)"
else
	@echo "$(GREEN)🌏 minirt : make done!$(WHITE)"
endif
	
clean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	rm -f $(SRC_MAN:.c=.o) $(SRC_MAN:.c=.d)
	rm -f $(SRC_BONUS:.c=.o) $(SRC_BONUS:.c=.d)
	@echo "$(BLUE)🌏 minirt : clean done!$(WHITE)"

fclean:
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	rm -f $(SRC_MAN:.c=.o) $(SRC_MAN:.c=.d)
	rm -f $(SRC_BONUS:.c=.o) $(SRC_BONUS:.c=.d)
	rm -f $(NAME)
	@echo "$(BLUE)🌏 minirt : fclean done!$(WHITE)"

re: fclean
	@$(MAKE)

-include $(DEPS)

.PHONY: all clean fclean re bonus

