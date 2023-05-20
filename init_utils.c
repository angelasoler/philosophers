/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:21 by asoler            #+#    #+#             */
/*   Updated: 2023/05/04 00:51:57 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_data(char **args)
{
	int	col;
	int	row;

	row = 1;
	while (args[row])
	{
		col = 0;
		while (args[row][col])
		{
			if (!ft_isdigit(args[row][col]))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	init_philos(t_main	*data)
{
	int	id;
	int	ret;

	id = 0;
	ret = 0;
	while (id < data->n_philo)
	{
		data->actual_id = id;
		printf("there's %d philos in the room\n", id);
		data->dinner.philo[id].state = 0;
		if (gettimeofday(&data->dinner.philo[id].id, NULL))
		{
			ret = printf("Failed getting time of %d philo \n", id);
			return (ret);
		}
		if (pthread_create(&data->dinner.philo[id].philosopher, \
			NULL, table, (void *)&data->dinner.philo[id].id.tv_usec))
		{
			ret = printf("Philo thread %d fail\n", id);
			return (ret);
		}
		id++;
	}
	return (ret);
}

int	init_dinner(t_main *data)
{
	int	i;

	i = 0;
	data->dinner.philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->dinner.philo)
		return (printf("philo malloc fail\n"));
	data->dinner.fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->dinner.fork)
		return (printf("fork malloc fail\n"));
	if (pthread_mutex_init(&data->dinner.dinner, NULL))
		return (printf("Dinner Mutex fail\n"));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->dinner.fork[i], NULL))
			return (printf("fork %d mutex fail\n", i));
		i++;
	}
	return (init_philos(data));
}

int	init_data(t_main *data, char *args[])
{
	if (verify_data(args))
		return (printf("invalid arguments\n"));
	data->n_philo = ft_atoi(args[1]);
	data->t_die = ft_atoi(args[2]);
	data->t_eat = ft_atoi(args[3]);
	data->t_sleep = ft_atoi(args[4]);
	if (data->n_time_sleep)
		data->n_time_sleep = ft_atoi(args[5]);
	return (0);
}
