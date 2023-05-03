#include "philo.h"

void	free_data(t_main *data)
{
	free(data->dinner.philo);
	free(data->dinner.fork);
}

int	end_dinner(t_main *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dinner.dinner);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->dinner.fork[i]);
		i++;
	}
	pthread_exit(NULL);
	free_data(data);
	return (0);
}

void	*table(void	*arg)
{
	t_main		*data;
	// t_dinner	*dinner;

	data = arg;
	printf("Philo %d has sat at the table\n", data->actual_id);
	// while (1)
	// {

	// }
	pthread_exit(0);
	// return ((void *)0);
}
