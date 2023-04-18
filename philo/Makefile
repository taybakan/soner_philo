NAME = philo

SRCS = main.c table.c functions.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread 

FLAGS_DATARACE = -fsanitize=thread -g

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

data_race:
	@$(CC) $(FLAGS_DATARACE) $(SRCS) -o $(NAME)

clean:
	@rm -rf *.dSYM

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re