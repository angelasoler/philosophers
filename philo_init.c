/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:21 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 17:11:26 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher(t_philo *philo, t_philo *neighbor, t_dinner *dinner)
{
	philo->args = &dinner->args;
	philo->alert_end = &dinner->alert_end;
	philo->meal_counter = 0;
	philo->alert_end_mutex = &dinner->alert_end_mutex;
	philo->print_mutex = &dinner->print_mutex;
	philo->last_meal = gettime_milisec_convertion();
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

t_list	*init_philos(t_dinner *dinner)
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
		dinner->philo[id].id = id + 1;
		neig_id = id + 1;
		if (neig_id == n_philos)
			neig_id = 0;
		if (create_philosopher(&dinner->philo[id], \
			&dinner->philo[neig_id], dinner))
			return (NULL);
		alloc_philo_list(&list, &dinner->philo[id], &id);
		id++;
	}
	return (list);
}

int	init_fork_mutex(t_dinner *dinner, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		if (philo_init_mutex(&dinner->philo[i]))
			return (printf("%d mutex fail\n", i));
		i++;
	}
	pthread_mutex_init(&dinner->alert_end_mutex, NULL);
	pthread_mutex_init(&dinner->print_mutex, NULL);
	return (0);
}

int	init_threads(t_dinner *dinner, int n_philo, t_list	*list)
{
	create_threads(n_philo, dinner->philo);
	if (pthread_create(&dinner->monitor_thread, NULL, ft_lstiter, list))
		return (printf("Philo thread fail\n"));
	pthread_join(dinner->monitor_thread, NULL);
	end_dinner(dinner);
	freelist(list);
	return (0);
}

int	init_dinner(t_dinner *dinner)
{
	t_list	*list;
	int		n_philos;

	n_philos = dinner->args.n_philos;
	dinner->philo = ft_calloc(sizeof(t_philo), n_philos);
	if (!dinner->philo)
		return (printf("philo malloc fail\n"));
	init_fork_mutex(dinner, n_philos);
	list = init_philos(dinner);
	if (!list)
		return (printf("list alloc fail\n"));
	init_threads(dinner, n_philos, list);
	return (0);
}

int	init_data(t_args *data, char *args[])
{
	if (verify_data(args))
		return (printf("invalid arguments\n"));
	data->n_philos = ft_atoi(args[1]);
	if (data->n_philos <= 0)
		return (printf("invalid arguments\n"));
	data->t_die = ft_atoi(args[2]);
	data->t_eat = ft_atoi(args[3]);
	data->t_sleep = ft_atoi(args[4]);
	if (data->n_must_eat)
		data->n_must_eat = ft_atoi(args[5]);
	return (0);
}
