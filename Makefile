# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 15:38:03 by rburgsta          #+#    #+#              #
#    Updated: 2022/12/04 14:49:19 by rburgsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

FLAGS = -Wall -Wextra -Werror

FT_PATH = libft
LIBFT_INC = $(FT_PATH)

SRC = main.c
OBJ = $(SRC:%.c=%.o)

all: $(FT_PATH) $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) -o $(NAME) $(OBJ) -L$(FT_PATH) -lft

$(FT_PATH) :
	git clone git@github.com:PythonGermany/42_libft.git $(FT_PATH)
	make -C $(FT_PATH)

%.o: %.c
	cc -c $(FLAGS) -I$(LIBFT_INC) $^

clean :
	make -C $(FT_PATH) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(FT_PATH) fclean
	rm -rf $(NAME) $(FT_PATH)

re: fclean all