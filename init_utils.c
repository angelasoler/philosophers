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

int	init_philos(t_dinner *dinner)
{
	int	id;
	int	ret;
	int	n_philos;

	id = 0;
	ret = 0;
	n_philos = dinner->args.n_philos;
	while (id < n_philos)
	{
		if (gettimeofday(&dinner->philo[id].last_meal, NULL))
		{
			ret = printf("Failed getting time of %d philo \n", id);
			return (ret);
		}
		dinner->philo[id].id = id;
		dinner->philo[id].args = &dinner->args;
		if (id < (n_philos - 1))
			dinner->philo[id].neighbor = &dinner->philo[id + 1];
		else
			dinner->philo[id].neighbor = &dinner->philo[0];
		if (pthread_create(&dinner->philo[id].philosopher, \
			NULL, join_meal, (void *)&dinner->philo[id]))
		{
			ret = printf("Philo thread %d fail\n", id);
			return (ret);
		}
		id++;
	}
	return (ret);
}

int	init_dinner(t_dinner *dinner)
{
	int	i;
	int	n_philos;

	i = 0;
	n_philos = dinner->args.n_philos;
	dinner->philo = ft_calloc(sizeof(t_philo), n_philos);
	if (!dinner->philo)
		return (printf("philo malloc fail\n"));
	while (i < n_philos)
	{
		if (pthread_mutex_init(&dinner->philo[i].fork_mutex, NULL))
			return (printf("fork %d mutex fail\n", i));
		i++;
	}
	return (init_philos(dinner));
}

int	init_data(t_args *data, char *args[])
{
	if (verify_data(args))
		return (printf("invalid arguments\n"));
	data->n_philos = ft_atoi(args[1]);
	data->t_die = ft_atoi(args[2]);
	data->t_eat = ft_atoi(args[3]);
	data->t_sleep = ft_atoi(args[4]);
	if (data->n_must_eat)
		data->n_must_eat = ft_atoi(args[5]);
	return (0);
}
