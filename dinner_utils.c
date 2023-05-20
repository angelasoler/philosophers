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

void	join_meal(int *id)
{
	printf("Philo %d access shared resources (join meal)\n", *id);
}

void	free_data(t_main *data)
{
	free(data->dinner.philo);
	free(data->dinner.fork);
}

int	end_dinner(t_main *data)
{
	int	id;
	int	time;

	id = 0;
	pthread_mutex_destroy(&data->dinner.dinner);
	while (id < data->n_philo)
	{
		pthread_mutex_destroy(&data->dinner.fork[id]);
		pthread_join(data->dinner.philo[id].philosopher, \
					(void **)&data->dinner.philo[id].state);
		if (data->dinner.philo[id].state)
		{
			time = data->dinner.philo[id].state;
			printf("Philo %d leave the room\n", time);
		}
		id++;
	}
	free_data(data);
	return (0);
}

void	*table(void	*arg)
{
	join_meal((int *)arg);
	pthread_exit(arg);
	return ((void *)0);
}
