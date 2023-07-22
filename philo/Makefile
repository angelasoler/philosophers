NAME=philo

CCW=gcc -Wall -Werror -Wextra -g3

THREAD_FLAG=-lpthread

SRC=philo.c \
	philo_lib_utils.c \
	philo_ft_atoi.c \
	philo_init_utils.c \
	philo_dinner_utils.c \
	philo_linked_list.c

OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DIR=obj

BUILD=docker build -t philo .

RUN=docker run -it --name=philo \
	--mount type=bind,source=$(PWD),target=/src \
	philo:1.0 bash

EXEC=docker exec -ti philo bash

all: $(NAME)

$(NAME): $(OBJ)
	$(CCW) $(OBJ) $(THREAD_FLAG) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR) 
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
