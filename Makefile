# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2022/12/09 00:07:59 by rburgsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

FLAGS = -Wall -Wextra -Werror
LK_SAN = #-Wno-gnu-include-next -I/LeakSanitizer/include -L../LeakSanitizer/ -llsan -lc++

FT_PATH = libft
LIBFT_INC = $(FT_PATH)

SRC = push_swap.c push_swap_utils.c operations.c
OBJ = $(SRC:%.c=%.o)

BONUS_SRC = checker.c push_swap_utils.c operations.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(FT_PATH)
	cc $(FLAGS) $(LK_SAN) -o $(NAME) $(OBJ) -L$(FT_PATH) -lft

bonus : $(BONUS_OBJ)
	make -C $(FT_PATH)
	cc $(FLAGS) $(LK_SAN) -o checker $(BONUS_OBJ) -L$(FT_PATH) -lft

%.o : %.c
	cc -c $(FLAGS) -I$(LIBFT_INC) $^

clean :
	make -C $(FT_PATH) clean
	rm -rf $(OBJ) checker.o

fclean : clean
	make -C $(FT_PATH) fclean
	rm -rf $(NAME) checker

re : fclean all