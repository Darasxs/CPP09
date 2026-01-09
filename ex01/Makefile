.SILENT:

name = RPN
FLAGS = -Wall -Wextra -Werror -std=c++17
CC = c++

SRC =	main.cpp \
		RPN.cpp

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(name): $(OBJ)
	@if [ ! -d $(name) ]; then \
		echo "\n$(GREEN)$(name) compiled successfully!$(NC)"; \
		echo "\n"; \
		echo "run with: ./$(name)"; \
		echo "------------------------------------------------"; \
	fi
	$(CC) $(FLAGS) $(OBJ) -o $(name)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean re
