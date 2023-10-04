/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:21 by asoler            #+#    #+#             */
/*   Updated: 2023/10/03 22:06:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher(t_philo *philo, t_philo *neighbor)
{
	int	id;
	int	ret;

	ret = 0;
	id = philo->id + 1;
	if (gettimeofday(&philo->last_meal, NULL))
	{
		ret = printf("Failed getting time of %d philo \n", id);
		return (ret);
	}
	philo->neighbor = neighbor;
	return (0);
}

int	create_threads(int n_philos, t_philo *philo)
{
	int	id;
	int	ret;

	ret = 0;
	id = 0;
	while (id < n_philos)
	{
		if (pthread_create(&philo[id].philosopher, \
			NULL, join_meal, (void *)&philo[id]))
		{
			ret = printf("Philo thread %d fail\n", id);
			return (ret);
		}
		id++;
	}
	return (ret);
}

int	init_philos(t_dinner *dinner)
{
	int		id;
	int		n_philos;
	t_list	*list;
	int		neig_id;

	list = NULL;
	id = 0;
	n_philos = dinner->args.n_philos;
	while (id < n_philos)
	{
		dinner->philo[id].args = &dinner->args;
		dinner->philo[id].id = id + 1;
		dinner->philo[id].meal_counter = 0;
		neig_id = id + 1;
		if (neig_id == n_philos)
			neig_id = 0;
		if (create_philosopher(&dinner->philo[id], &dinner->philo[neig_id]))
			return (-1);
		alloc_philo_list(&list, &dinner->philo[id], &id);
		id++;
	}
	create_threads(n_philos, dinner->philo);
	if (ft_lstiter(list, alert_dead, n_philos))
		return (1);
	// if (pthread_create(&dinner->monitoring_thread, NULL, alert_dead, dinner->philo))
	// {
	// 	ret = printf("Philo thread %d fail\n", id);
	// 	return (ret);
	// }
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
		if (philo_init_mutex(&dinner->philo[i]))
			return (printf("%d mutex fail\n", i));
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
