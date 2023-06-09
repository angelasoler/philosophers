NAME=philo

CCW=gcc -Wall -Werror -Wextra -g3

THREAD_FLAG=-lpthread

SRC=philo.c \
	lib_utils.c \
	ft_atoi.c \
	init_utils.c \
	dinner_utils.c

OBJ=$(SRC:.c=.o)

BUILD=docker build -t philo .

RUN=docker run -it --name=philo \
	--mount type=bind,source=$(PWD),target=/src \
	philo:1.0 bash

EXEC=docker exec -ti philo bash

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

run:
	$(RUN)

build:
	$(BUILD)

start: 
	docker start philo

image: start
	$(EXEC)

.PONHY: re fclean clean all
