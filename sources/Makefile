# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/06/16 21:18:29 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

#-fsanitize=address -g3
NAME	=	../fractol
NAME_SAVE = ../fractol_save
DEPS = ../includes/fractol.h

SRC		= 	error_opencl.c				\
			exit.c						\
			main.c						\
			ocl_calcul_ifs_point.c		\
			ocl_define_colore.c			\
			ocl_draw_line.c				\
			ocl_init.c					\
			ocl_init_ifs.c				\
			read_file.c


OBJ			= $(SRC:.c=.o)
LIB_DIR		= -L ../libft -L ../c_maths -L ../vec_math -L ../minilibx_macos
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext

LIB_NAME	= -lft -lc_maths -lvec_math -lmlx

FRAMEWORK	= -framework OpenGl -framework AppKit -framework opencl

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(LIB_DIR) $(LIB_NAME) $(FRAMEWORK)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes -I ../c_maths  


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
