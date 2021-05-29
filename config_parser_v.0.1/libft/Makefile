# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbeach <rbeach@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 14:22:17 by rbeach            #+#    #+#              #
#    Updated: 2021/05/02 16:10:01 by rbeach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang++

FLAGS = -Wall -Werror -Wextra

HEADER = libft.h

HEADER_DIR = .

S_DIR = .

O_DIR = obj

SRCS = ft_memset.cpp\
ft_bzero.cpp\
ft_memcpy.cpp\
ft_memccpy.cpp\
ft_memmove.cpp\
ft_memchr.cpp\
ft_memcmp.cpp\
ft_strlen.cpp\
ft_strlcpy.cpp\
ft_strlcat.cpp\
ft_strchr.cpp\
ft_strrchr.cpp\
ft_strnstr.cpp\
ft_strncmp.cpp\
ft_atoi.cpp\
ft_isalpha.cpp\
ft_isdigit.cpp\
ft_isalnum.cpp\
ft_isascii.cpp\
ft_isprint.cpp\
ft_toupper.cpp\
ft_tolower.cpp\
ft_calloc.cpp\
ft_strdup.cpp\
ft_substr.cpp\
ft_strjoin.cpp\
ft_strtrim.cpp\
ft_split.cpp\
ft_itoa.cpp\
ft_strmapi.cpp\
ft_putchar_fd.cpp\
ft_putstr_fd.cpp\
ft_putendl_fd.cpp\
ft_putnbr_fd.cpp\
ft_itoagr.cpp\
ft_strlower.cpp\
ft_strcatchr.cpp\
ft_symclone.cpp\
ft_strlens.cpp

OBJECTS = $(addprefix $(O_DIR)/,$(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER_DIR)/$(HEADER)
	ar rcs $(NAME) $(OBJECTS)

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	@mkdir -p $(O_DIR)
	$(CC) $(FLAGS) -I $(HEADER_DIR) -o $@ -c $<

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
