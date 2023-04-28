#include "philo.h"

void	table(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Philo %d has sat at the table", philo->id);
}

int	init_philos(t_main	*data)
{
	int	id;

	id = 0;
	while (id < data->n_philo)
	{
		data->dinner.philo[i].id = id;
		if (pthread_create(&data->dinner.philo[i].philosopher, NULL, table, &data->dinner.philo[i]))
			return (printf("Philo threat %d fail", id));
		id++;
	}
}

int	init_dinner(t_main *data)
{
	int	i;

	i = 0;
	data->dinner.philo = malloc(sizeof(t_philo) * data->n_philo);
	if (pthread_mutex_init(&data->dinner, NULL));
		return (printf("Dinner Mutex fail\n"));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->dinner.philo,NULL))
			return (printf("Philo %d mutex fail\n"));
		i++;
	}
	return (init_philos(data));
}

void	init_data(t_main *data, char *args[])
{
	data->n_philos = atoi(args[1]);
	data->t_die = atoi(args[2]);
	data->t_eat = atoi(args[3]);
	data->t_sleep = atoi(args[4]);
	data->n_time_sleep = atoi(args[5]);
}

int main(int argc, char *argv[])
{
	t_main	data;

	if (argc != 6)
		return (printf("Arguments are wrong"));
	init_data(data, argv);
	if (init_dinner(data))
		return (printf("init philo fail"));
	// end_dinner(data);
	return (0);
}
