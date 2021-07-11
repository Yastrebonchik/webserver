NAME = webserver

CC = clang++

CONFPAR_DIR = config_parser_v.0.1

CONFPAR = libconfpar.a

FLAGS = -Wall -Werror -Wextra -std=c++98

HEADERS = methods.h RequestHeaders.hpp ResponseHeaders.hpp ConnectionClass.hpp utils.hpp ConnectionHandling.hpp cgi.hpp

HEADER_DIR = includes

S_DIR = srcs

O_DIR = obj

SRCS = main.cpp RequestHeaders.cpp ResponseHeaders.cpp methods.cpp ConnectionClass.cpp utils.cpp \
ConnectionHandling.cpp cgi.cpp

OBJECTS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJECTS) confpar srcs/main.cpp
	clang++ -o $(NAME) $(OBJECTS) -L$(CONFPAR_DIR) -I$(HEADER_DIR) -lconfpar
	#clang++ main.cpp libconfpar.a -L$(LIBFT_DIR) -lft

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	mkdir -p $(O_DIR)
	$(CC) $(FLAGS) -I$(CONFPAR_DIR)/includes -I$(HEADER_DIR) -o $@ -c $<

confpar:
	$(MAKE) -C $(CONFPAR_DIR)

clean:
	rm -rf $(O_DIR)
	make clean -C $(CONFPAR_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(CONFPAR_DIR)

re: fclean all

.PHONY: all clean fclean re confpar