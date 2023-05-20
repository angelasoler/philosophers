BUILD=docker build -t philo .

RUN=docker run -it --name=philo \
			--mount type=bind,source=${PWD},target=/src \
			philo:1.0 bash

EXEC=docker exec -ti philo bash

all: image
	gcc -pthread test.c && ./a.out

run: build
	$(RUN)

build:
	$(BUILD)

start: 
	docker start philo

image: start
	$(EXEC)

