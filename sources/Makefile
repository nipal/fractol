# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2016/11/10 18:37:46 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-fsanitize=address -g3
NAME	=	../fractol
NAME_SAVE = ../fractol_save
SRC		= 	main.c \
			draw_line.c \
			koch_generalise.c \
			calcul_madelbrot.c \
			mlx_env.c \
			print_somthing.c \
			hook.c \
			polygone_new.c \
			polygone_destroy.c \
			polygone_transfrom.c \
			polygone_print.c \
			polygone_maj.c \
			modify_model.c \
			color_transpose.c \
			new_printing.c \
			init_win.c \
			new_hook.c \
			param_koch.c \
			segment_mecanique.c \
			printing_koch_final.c \
			sliding_button.c \
			exit.c 

OBJ		= $(SRC:.c=.o)

#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 


FLAGS-DEBUG = -g3 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		gcc -o $(NAME) $(CFLAGS) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-lmlx -framework OpenGL -framework AppKit
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#		 cp -f $(NAME) $(NAME_SAVE) 


%.o: %.c
	gcc -o $@ -c $< -I ../includes -I ../c_maths $(CFLAGS)
	# -I /usr/includes/

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
