# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:22:17 by rbeach            #+#    #+#              #
#    Updated: 2021/07/10 19:07:07 by rbeach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libconfpar.a

CC = clang++

LIBFT_DIR = libft

LIBFT = libft.a

FLAGS = -std=c++98 -Wall -Werror -Wextra -g

HEADERS = config_check.hpp config_parser.hpp ConfigClass.hpp

HEADER_DIR = includes

S_DIR = src

O_DIR = obj

SRCS = config_parser.cpp config_check.cpp ConfigClass.cpp LocationClass.cpp utils.cpp

OBJECTS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS) main.cpp
	ar rcs $(NAME) $(OBJECTS)
	

main: $(NAME)
	$(CC) main.cpp libconfpar.a

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(HEADER_DIR)/*.hpp
	mkdir -p $(O_DIR)
	$(CC) $(FLAGS) -I$(HEADER_DIR) -o $@ -c $<

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
