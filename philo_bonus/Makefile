.PHONY: all clean fclean re

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = philo_bonus

CFILES = main.c check_input.c utils.c time.c safe_functions.c data_init.c philo_life.c dinner.c

OBJ = $(patsubst %.c, %.o, $(CFILES))
B_OBJ = $(patsubst %.c, %.o, $(BFILES))

all: $(NAME)

$(OBJ): %.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -pthread -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all