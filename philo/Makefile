.PHONY: all clean fclean re

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = philo

CFILES = main.c ft_error.c check_input.c get_set.c safe_functions.c time.c\
		 data_init.c dinner_manager.c dinner.c philo_life.c

OBJ = $(patsubst %.c, %.o, $(CFILES))
B_OBJ = $(patsubst %.c, %.o, $(BFILES))

all: $(NAME)

$(OBJ): %.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -pthread -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all