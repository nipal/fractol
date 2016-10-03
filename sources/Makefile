# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by jpirsch           #+#    #+#              #
#    Updated: 2016/10/03 22:01:01 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../fratctol
SRC		= 	main.c \
			mlx_env.c \
			print_somthing.c \
			hook.c \
			hook_2.c \
			hook_3.c \
			hook_cam.c \
		 	drawline.c \
			draw_line_triangle.c \
			draw_link_face.c \
			map_adapt_to_cam.c \
			maped.c \
			print_map.c \
			print_map_end.c \
			cam.c \
			exit.c \
			its_parse_time.c \
			its_parse_time_2.c 

OBJ		= $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3

FLAGS-DEBUG = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		gcc -o $(NAME) $(FLAGS) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-lmlx -framework OpenGL -framework AppKit
	#	-L /usr/lib/ -lmlx -lm -lX11 -lXext


$(OBJ):
	gcc -c $(FLAGS) $(SRC) -I ../includes -I ../c_maths# -I /usr/includes/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

gdb: fclean
		gcc -c $(FLAGS-DEBUG) $(SRC) -I ../includes -I ../c_maths# -I /usr/includes/
		gcc -o $(NAME) $(FLAGS-DEBUG) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-L /usr/lib/ -lmlx -lm -lX11 -lXext
