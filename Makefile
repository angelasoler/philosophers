DOCKER_RUN=docker run -it --rm --name=philo \
			--mount type=bind,source=${PWD},target=/src \
			philo:1.0 bash

all:
	$(DOCKER_RUN)