/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 20:10:16 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_a_fork(t_philo *philo)
{
	int		first_fork;
	int		second_fork;
	t_now	time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is thinking\n", time_now.tv_usec, philo->id);
	while (philo->fork == BUSY)
		continue ;
	first_fork = pthread_mutex_lock(&philo->fork_mutex);
	if (!first_fork)
	{
		gettimeofday(&time_now, NULL);
		printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
		philo->fork = BUSY;
	}
	while (philo->neighbor->fork == BUSY)
		continue ;
	second_fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
	if (!second_fork)
	{
		gettimeofday(&time_now, NULL);
		printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
		philo->fork = BUSY;
	}
}

int	philo_eat(t_philo *philo)
{
	static int	eat_counter;
	t_now		time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is eating\n", time_now.tv_usec, philo->id);
	usleep(philo->args->t_eat);
	philo->fork = AVALIBLE;
	philo->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	if (philo->args->n_must_eat)
	{
		eat_counter++;
		if (eat_counter == philo->args->n_must_eat)
			return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	t_now	time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is sleeping\n", time_now.tv_usec, philo->id);
	usleep(philo->args->t_sleep);
}

void	set_at_the_table(t_philo *philo)
{
	philo_take_a_fork(philo);
	if (philo_eat(philo))
		return ;
	philo_sleep(philo);
}

void	*join_meal(void	*arg)
{
	int			*ret;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ret = ft_calloc(sizeof(int), 1);
	*ret = philo->id;
	set_at_the_table(philo);
	philo->im_done = 1;
	pthread_exit((void *)ret);
	return ((void *)0);
}
