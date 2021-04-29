# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lessie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 15:18:20 by lessie            #+#    #+#              #
#    Updated: 2021/04/29 15:25:37 by lessie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_HEADERS	= ./includes/

DIR_SRCS	= ./srcs/

SRC			=	image/image.c \
                color_and_light/color.c color_and_light/light.c \
                figures/cylinder.c figures/plane.c figures/sphere.c \
                figures/triangle.c \
                intersections/all_intersects.c intersections/inter_cylinder.c \
                intersections/inter_plane.c intersections/inter_sphere.c \
                intersections/inter_triang.c \
                matrices/matrix.c \
                parser/amb_parse.c parser/ascii_convert.c parser/cam_parse.c \
                parser/check_eat_space.c parser/cylinder_parse.c parser/light_parse.c \
                parser/parse_vec.c parser/parsing.c parser/plane_parse.c \
                parser/res_parse.c parser/sphere_parse.c parser/triangle_parse.c \
                parser/square_parse.c \
                scene/camera.c scene/scene.c \
                tracer/closest.c tracer/ray_tracing.c \
                utils/ft_utils.c utils/ft_utils_str.c utils/get_next_line.c \
                utils/putnbr.c \
				vectors/vector.c vectors/vector_2.c vectors/vec_stack.c \
				vectors/vec_stack_2.c vectors/vec_utils.c \
				bmp_creator/create_bmp.c bmp_creator/bmp_utils.c \
				main.c \

SRCS		= $(addprefix $(DIR_SRCS), $(SRC))

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

LIBMLX		= libmlx.a

GCC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra -g

%.o:%.c
			$(GCC) $(CFLAGS) -I$(DIR_HEADERS) -Imlx -c $< -o $@

$(NAME):	$(OBJS)
			make -C ./minilibx_opengl
			cp ./minilibx_opengl/libmlx.a .
			$(GCC) $(CFLAGS) -L. -lmlx -framework OpenGL -framework AppKit -I./$(DIR_HEADERS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			make clean -C ./minilibx_opengl
			$(RM) $(LIBMLX)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
