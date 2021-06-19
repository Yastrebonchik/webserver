# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:22:17 by rbeach            #+#    #+#              #
#    Updated: 2021/06/19 11:47:15 by rbeach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libconfpar.a

CC = clang++

LIBFT_DIR = libft

LIBFT = libft.a

FLAGS = -std=c++98#-Wall -Werror -Wextra

TEST_FLAGS = -o3 -g3

HEADERS = config_check.hpp config_parser.hpp ConfigClass.hpp

HEADER_DIR = includes

S_DIR = src

O_DIR = obj

SRCS = config_parser.cpp config_check.cpp ConfigClass.cpp utils.cpp

OBJECTS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS) main.cpp
	ar rcs $(NAME) $(OBJECTS)
	clang++ main.cpp libconfpar.a

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	mkdir -p $(O_DIR)
	$(CC) $(FLAGS) -I$(HEADER_DIR) -I../libft -o $@ -c $<

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
