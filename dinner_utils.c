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

void	join_meal(long int *id)
{
	printf("Philo %ld access shared resources (join meal)\n", *id);
}

void	free_data(t_main *data)
{
	free(data->dinner.philo);
	free(data->dinner.fork);
}

int	end_dinner(t_main *data)
{
	int			id;

	id = 0;
	pthread_mutex_destroy(&data->dinner.dinner);
	while (id < data->n_philo)
	{
		pthread_mutex_destroy(&data->dinner.fork[id]);
		pthread_join(data->dinner.philo[id].philosopher, \
					(void **)&data->dinner.philo[id].ret);
		if (data->dinner.philo[id].ret)
		{
			printf("Philo %ld leaves the room\n", *data->dinner.philo[id].ret);
			free(data->dinner.philo[id].ret);
		}
		id++;
	}
	free_data(data);
	return (0);
}

void	*table(void	*arg)
{
	long int	*ret;
	long int	*ret2;

	ret2 = ft_calloc(sizeof(long int), 1);
	join_meal((long int *)arg);
	ret = (long int *)arg;
	*ret2 = *ret;
	pthread_exit((void *)ret2);
	return ((void *)0);
}
