# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by jpirsch           #+#    #+#              #
#    Updated: 2016/12/09 09:41:12 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

#-g -fsanitize=address 
export CFLAGS	=  -g -fsanitize=address  
export CC	= clang

#-g -fsanitize=address


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
