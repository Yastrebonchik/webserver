# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcedra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/27 16:34:05 by kcedra            #+#    #+#              #
#    Updated: 2020/05/28 19:15:53 by kcedra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = clang++

NAME = libft.a

HEADER = libft.h

SOURCES = ft_memchr.cpp ft_strlcpy.cpp ft_memccpy.cpp ft_strlen.cpp ft_atoi.cpp ft_memcpy.cpp ft_strmapi.cpp ft_bzero.cpp ft_memset.cpp ft_strncmp.cpp\
ft_calloc.cpp ft_putchar_fd.cpp ft_strnstr.cpp ft_isalnum.cpp ft_putendl_fd.cpp ft_strrchr.cpp ft_isalpha.cpp ft_putnbr_fd.cpp ft_strtrim.cpp\
ft_isascii.cpp ft_putstr_fd.cpp ft_substr.cpp ft_isdigit.cpp ft_split.cpp ft_tolower.cpp ft_isprint.cpp ft_strchr.cpp ft_toupper.cpp ft_itoa.cpp\
ft_strdup.cpp ft_strjoin.cpp ft_strlcat.cpp ft_memcmp.cpp ft_memmove.cpp

O_FILES = $(SOURCES:.cpp=.o)

BONUS_SOURCES = ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c ft_lstiter.c\
ft_lstmap.c

BONUS_O_FILES = $(BONUS_SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror

.c.o:	
	$(COMPILER) $(FLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(O_FILES) $(HEADER)
	ar rcs $(NAME) $(O_FILES)

clean:
	rm -f $(O_FILES)
	rm -f $(BONUS_O_FILES)

fclean:	clean
	rm -f $(NAME)

bonus: $(O_FILES) $(BONUS_O_FILES)
	ar rcs $(NAME) $(O_FILES) $(BONUS_O_FILES)

re:	fclean all
