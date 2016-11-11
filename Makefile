# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2016/11/11 16:57:39 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-g -fsanitize=address 
export CFLAGS	= -Wall -Wextra -Werror -Ofast 
#export CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address  


NAME			= fdf
SRC_DIR			= ./sources
LIB_FT			= ./libft
LIB_M			= ./c_maths

all:
	make -C $(LIB_FT)
	make -C $(LIB_M)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_FT)  clean
	make -C $(LIB_M)  clean
	make -C $(SRC_DIR) clean

fclean: clean
	make -C $(LIB_FT)  fclean
	make -C $(LIB_M)  fclean
	make -C $(SRC_DIR) fclean

re: fclean all

gdb:
	make -C $(LIB_FT) gdb
	make -C $(LIB_M) gdb
	make -C $(SRC_DIR) gdb
