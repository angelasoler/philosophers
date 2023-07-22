/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:21 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 19:51:39 by angelasoler      ###   ########.fr       */
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
// [_] use n_philos and id from philo struct
int	create_philosopher(t_philo *philo, t_philo *last_neighbor, t_philo *first_neighbor)
{
	int	id;
	int	ret;
	int n_philos;

	ret = 0;
	id = philo->id;
	n_philos = philo->args->n_philos;
	if (gettimeofday(&philo->last_meal, NULL))
	{
		ret = printf("Failed getting time of %d philo \n", id);
		return (ret);
	}
	if (id < (n_philos - 1))
		philo->neighbor = last_neighbor;
	else
		philo->neighbor = first_neighbor;
	if (pthread_create(&philo->philosopher, \
		NULL, join_meal, (void *)&philo))
	{
		ret = printf("Philo thread %d fail\n", id);
		return (ret);
	}
	return (0);
}

int	verify_philos_state(t_philo *philo)
{
	if (philo->im_done)
		return (1);
	return (0);
}

int	ft_lstiter(t_list *lst, int (f)(void *))
{
	t_list	*aux;

	aux = lst;
	while (aux)
	{
		if (f(aux->philo))
			return (printf("philo %d starved\n", aux->philo->id));
		else
			if (verify_philos_state(aux->philo))
				return (0);
		aux = aux->next;
	}
	printf("circle linked list fail\n");
	exit(1);
	return (0);
}

int	init_philos(t_dinner *dinner)
{
	int		id;
	int		n_philos;
	t_list	*list;

	list = NULL;
	id = 0;
	n_philos = dinner->args.n_philos;
	while (id < n_philos)
	{
		dinner->philo[id].args = &dinner->args;
		dinner->philo->id = id;
		if (create_philosopher(&dinner->philo[id], &dinner->philo[id + 1], &dinner->philo[0]))
			return (-1);
		alloc_philo_list(&list, &dinner->philo[id], id);
		id++;
	}
	if (ft_lstiter(list, alert_dead))
		return (printf("somebody starved, attach not join?\n"));
	else
		printf("dinner is almost over, everybody satisfied\n");
	return (0);
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
