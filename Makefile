# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iganiev <iganiev@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 15:30:22 by iganiev           #+#    #+#              #
#    Updated: 2023/08/11 15:30:22 by iganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = philosophers.c utils.c \

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

$(NAME): $(OBJ)
		cc $(OBJ)  $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re