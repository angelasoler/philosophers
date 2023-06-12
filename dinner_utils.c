/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/05/04 00:49:17 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_meal(long int id, long int last_meal)
{
	struct timeval	actual_time;

	printf("Philo %ld access join meal, last_meal = %ld\n", id, last_meal);
	gettimeofday(&actual_time, NULL);
	printf("has not eaten from %ld miliseconds\n", \
			actual_time.tv_usec - last_meal);
}

int	end_dinner(t_main *data)
{
	int	id;
	int	*thread_ret;

	id = 0;
	thread_ret = NULL;
	while (id < data->n_philo)
	{
		pthread_mutex_destroy(&data->dinner.philo[id].fork_mutex);
		pthread_join(data->dinner.philo[id].philosopher, (void **)&thread_ret);
		if (thread_ret)
		{
			printf("Philo %d leaves the room\n", *thread_ret);
			free(thread_ret);
		}
		id++;
	}
	free(data->dinner.philo);
	return (0);
}

void	*table(void	*arg)
{
	int			*aux;
	int			*ret;
	t_philo		*philo;
	long int	last_meal;

	philo = (t_philo *)arg;
	last_meal = philo->last_meal.tv_usec;
	ret = ft_calloc(sizeof(int), 1);
	join_meal(philo->id, last_meal);
	aux = &philo->id;
	*ret = *aux;
	pthread_exit((void *)ret);
	return ((void *)0);
}
