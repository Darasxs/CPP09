.SILENT:

NAME = PmergeMe
FLAGS = -Wall -Wextra -Werror -std=c++17
CC = c++

SRC =	main.cpp \
		PmergeMe.cpp

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -d $(NAME) ]; then \
		echo "\n$(GREEN)$(NAME) compiled successfully!$(NC)"; \
		echo "\n"; \
		echo "run with: ./$(NAME)"; \
		echo "------------------------------------------------"; \
	fi
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re