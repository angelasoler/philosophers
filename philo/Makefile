NAME=philo

CCW=gcc -Wall -Werror -Wextra -g3

THREAD_FLAG=-lpthread

SRC=philo.c \
	lib_utils.c \
	ft_atoi.c \
	init_utils.c \
	dinner_utils.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CCW) $(OBJ) $(THREAD_FLAG) -o $(NAME)

%.o: %.c
	$(CCW) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf *.o

.PONHY: re fclean clean all
