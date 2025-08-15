NAME	= PmergeMe
CC		= c++
CFLAG	= -Wall -Wextra -Werror -std=c++17
SRC		= main.cpp PmergeMe.cpp
OBJ		= $(SRC:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all