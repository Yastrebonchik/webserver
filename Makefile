NAME = webserver

CC = clang++

LIBFT_DIR = libft

LIBFT = libft.a

CONFPAR_DIR = config_parser_v.0.1

CONFPAR = libconfpar.a

FLAGS = -Wall -Werror -Wextra -std=c++98

#TEST_FLAGS = -o3 -g3

HEADERS = methods.h RequestHeaders.hpp ResponseHeaders.hpp

#HEADER_DIR = includes

#S_DIR = src

O_DIR = obj

SRCS = main.cpp RequestHeaders.cpp ResponseHeaders.cpp methods.cpp #cgi.cpp

OBJECTS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS) libft confpar main.cpp
	clang++ -o $(NAME) $(OBJECTS) -L$(CONFPAR_DIR) -lconfpar -L$(LIBFT_DIR) -lft
	#clang++ main.cpp libconfpar.a -L$(LIBFT_DIR) -lft

$(O_DIR)/%.o: %.cpp
	mkdir -p $(O_DIR)
	$(CC) $(FLAGS) -I$(LIBFT_DIR) -I$(CONFPAR_DIR)/includes -o $@ -c $<

libft:
	$(MAKE) -C $(LIBFT_DIR)

confpar:
	$(MAKE) -C $(CONFPAR_DIR)

clean:
	rm -rf $(O_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(CONFPAR_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(CONFPAR_DIR)

re: fclean all

.PHONY: all clean fclean re libft