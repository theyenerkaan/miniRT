# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/21 00:00:00 by kaan              #+#    #+#              #
#    Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################
#                  VARIABLES                  #
###############################################

NAME                =   miniRT
HEADER              =   minirt.h
CC                  =   cc
CFLAGS              =   -Wall -Wextra -Werror -g
LIBFT               =   libft/libft.a
LIBFTDIR            =   libft
GNL                 =   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNLDIR              =   get_next_line
MLX                 =   minilibx-linux/libmlx.a
MLXDIR              =   minilibx-linux
INCLUDES            =   -I. -I$(MLXDIR) -I$(LIBFTDIR) -I$(GNLDIR)
LIBS                =   -L$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft -lXext -lX11 -lm

SRCS                =   src/main.c \
                        src/utils.c \
                        src/math/vec3_basic.c \
                        src/math/vec3_ops.c \
                        src/math/color.c \
                        src/math/color_utils.c \
                        src/math/ray.c \
                        src/parser/parse_common.c \
                        src/parser/parse_elements.c \
                        src/parser/parse_objects.c \
                        src/parser/parse_scene.c \
                        src/parser/parse_utils.c \
                        src/render/camera.c \
                        src/render/trace.c \
                        src/render/render.c \
                        src/intersections/hit_sphere.c \
                        src/intersections/hit_plane.c \
                        src/intersections/hit_cylinder.c \
                        src/intersections/hit_cylinder_utils.c \
                        src/shading/shading.c \
                        src/shading/shadow.c \
                        src/mlx/mlx_init.c \
                        src/mlx/mlx_hooks.c \
                        $(GNL)

OBJS                =   $(SRCS:.c=.o)

###############################################
#                 COLORS                       #
###############################################

COLOR_RED           =   \033[0;31m
COLOR_BOLD_RED      =   \033[1;31m
COLOR_LIGHT_RED     =   \033[0;91m
COLOR_GREEN         =   \033[0;32m
COLOR_BOLD_GREEN    =   \033[1;32m
COLOR_LIGHT_GREEN   =   \033[0;92m
COLOR_BLUE          =   \033[0;34m
COLOR_BOLD_BLUE     =   \033[1;34m
COLOR_LIGHT_BLUE    =   \033[0;94m
COLOR_PURPLE        =   \033[0;35m
COLOR_BOLD_PURPLE   =   \033[1;35m
COLOR_LIGHT_PURPLE  =   \033[0;95m
COLOR_CYAN          =   \033[0;36m
COLOR_BOLD_CYAN     =   \033[1;36m
COLOR_LIGHT_CYAN    =   \033[0;96m
COLOR_RESET         =   \033[0m

###############################################
#                  TARGETS                    #
###############################################

all: $(LIBFT) $(GNL) $(MLX) $(NAME)

$(LIBFT): $(LIBFTDIR)
	@make -C $(LIBFTDIR) > /dev/null 2>&1

$(LIBFTDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning libft repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone git@github.com:theyenerkaan/libft.git $(LIBFTDIR)
	@echo "$(COLOR_RESET)"

$(GNL): $(GNLDIR)

$(GNLDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning get_next_line repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone git@github.com:theyenerkaan/get_next_line_true.git $(GNLDIR)
	@echo "$(COLOR_RESET)"

$(MLX): $(MLXDIR)
	@make -C $(MLXDIR) > /dev/null 2>&1

$(MLXDIR):
	@echo "$(COLOR_BOLD_CYAN)🌀 cloning minilibx-linux repository...$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLXDIR)
	@echo "$(COLOR_RESET)"

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(COLOR_BOLD_GREEN)✔ Compilation complete!$(COLOR_RESET)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

valgrind: $(NAME)
	@echo "$(COLOR_BOLD_CYAN)🔍 Running Valgrind for memory leaks...$(COLOR_RESET)"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind_out.txt ./$(NAME) $(ARGS)
	@echo "$(COLOR_BOLD_GREEN)✔ Valgrind check completed. See valgrind_out.txt$(COLOR_RESET)"

clean:
	@echo "$(COLOR_LIGHT_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@rm -f $(OBJS)
	@if [ -d "$(LIBFTDIR)" ]; then \
		make clean -C $(LIBFTDIR) > /dev/null 2>&1; \
	fi
	@if [ -d "$(MLXDIR)" ]; then \
		make clean -C $(MLXDIR) > /dev/null 2>&1; \
	fi
	@echo "$(COLOR_LIGHT_RED)🧹 Object files cleaned.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_LIGHT_RED)🧹 removing object files and executables...$(COLOR_RESET)"
	@rm -f $(NAME)
	@if [ -d "$(LIBFTDIR)" ]; then \
		make fclean -C $(LIBFTDIR) > /dev/null 2>&1; \
	fi
	@if [ -d "$(MLXDIR)" ]; then \
		make clean -C $(MLXDIR) > /dev/null 2>&1; \
	fi
	@echo "$(COLOR_LIGHT_RED)🧹 all object files and executables removed.$(COLOR_RESET)"

clear: fclean
	@rm -rf $(MLXDIR) $(LIBFTDIR) $(GNLDIR)

norm:
	@rm -rf $(MLXDIR) $(LIBFTDIR) $(GNLDIR)
	norminette

re: fclean all
	@echo "$(COLOR_BOLD_GREEN)♻️  recompiled successfully... $(COLOR_RESET)"

.PHONY: all clean fclean re valgrind clear norm
