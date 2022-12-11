# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2022/12/07 22:24:35 by rburgsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

FLAGS = -Wall -Wextra -Werror
LK_SAN = #-Wno-gnu-include-next -I/LeakSanitizer/include -L./LeakSanitizer/ -llsan -lc++

FT_PATH = libft
LIBFT_INC = $(FT_PATH)

SRC = main.c operations.c push_swap_utils.c
OBJ = $(SRC:%.c=%.o)

all : $(FT_PATH) $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(LK_SAN) -o $(NAME) $(OBJ) -L$(FT_PATH) -lft

bonus : checker.o operations.o push_swap_utils.o
	cc $(FLAGS) $(LK_SAN) -o checker $^ -L$(FT_PATH) -lft

$(FT_PATH) :
	git clone git@github.com:PythonGermany/42_libft.git $(FT_PATH)
	make -C $(FT_PATH)

%.o : %.c
	cc -c $(FLAGS) -I$(LIBFT_INC) $^

clean :
	make -C $(FT_PATH) clean
	rm -rf $(OBJ) checker.o

fclean : clean
	make -C $(FT_PATH) fclean
	rm -rf $(NAME) $(FT_PATH) checker

re : fclean all