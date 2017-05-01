# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2017/05/01 06:13:11 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

# -g -fsanitize=address 
# -Ofast
#  -Wall -Wextra -Werror
#export CFLAGS	= -g -fsanitize=address 
export CFLAGS	= -O3 -Werror #-Wall -Wextra
#export CFLAGS	= -g3 #-Wall -Wextra

#-fsanitize=address
export CC	= gcc

#-g -fsanitize=address


NAME			= fdf
SRC_DIR			= ./sources
LIB_FT			= ./libft
LIB_M			= ./c_maths
LIB_MV			= ./vec_math
LIB_MLX			= ./minilibx_macos

all:
	make -C $(LIB_MLX)
	make -C $(LIB_FT)
	make -C $(LIB_M)
	make -C $(LIB_MV)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_MLX)	clean
	make -C $(LIB_FT)  clean
	make -C $(LIB_M)  clean
	make -C $(LIB_MV)  clean
	make -C $(SRC_DIR) clean

fclean: clean
	make -C $(LIB_FT)  fclean
	make -C $(LIB_M)  fclean
	make -C $(LIB_MV)  fclean
	make -C $(SRC_DIR) fclean

re: fclean all
