# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lessie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 15:18:20 by lessie            #+#    #+#              #
#    Updated: 2021/02/26 14:59:10 by lessie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_HEADERS	= ./includes/

DIR_SRCS	= ./srcs/

SRC			=	color_and_light/color.c color_and_light/light.c \
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
                scene/camera.c scene/scene.c \
                tracer/closest.c tracer/ray_tracing.c \
                utils/ft_utils.c utils/ft_utils_str.c utils/get_next_line.c \
				vectors/vector.c vectors/vector_2.c \
				bmp_creator/create_bmp.c bmp_creator/bmp_utils.c \
				main.c \

SRCS		= $(addprefix $(DIR_SRCS), $(SRC))

OBJS		= $(SRCS:.c=.o)

NAME		= miniRT

LIBMLX		= libmlx.dylib

GCC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra

%.o: %.c
			$(GCC) $(CFLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
			make -C ./minilibx_mms_20200219
			cp ./minilibx_mms_20200219/libmlx.dylib .
			$(GCC) $(CFLAGS) -I./$(DIR_HEADERS) $(LIBMLX) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			make clean -C ./minilibx_mms_20200219
			$(RM) $(LIBMLX)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
