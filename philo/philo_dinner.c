/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 23:20:17 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

int	block_fork(t_philo **philo, int id)
{
	t_now		time_now;
	// static int	count_think;
	int			fork;

	// while ((*philo)->fork == BUSY)
	// {
	// 	gettimeofday(&time_now, NULL);
	// 	if (count_think == 0)
	// 		printf("%ld %d is thinking\n", time_now.tv_usec, id);
	// 	usleep(10);
	// 	count_think++;
	// }
	fork = pthread_mutex_lock(&(*philo)->fork_mutex);
	if (!fork)
	{
		gettimeofday(&time_now, NULL);
		printf("%ld %d has taken a fork\n", time_now.tv_usec, id);
		(*philo)->fork = BUSY;
	}
	else
	{
		if ((*philo)->id != id)
			printf("error: philo %d could not block neighbor's fork: %d\n", (*philo)->id, id);
		else
			printf("error: philo %d could not block his fork\n", id);
		return (1);
	}
	return (0);
}

int	philo_take_a_fork(t_philo *philo)
{
	if (block_fork(&philo, philo->id))
		return (1);
	if (block_fork(&philo->neighbor, philo->id))
		return (1);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	static int	eat_counter;
	t_now		time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is eating\n", time_now.tv_usec, philo->id);
	usleep(philo->args->t_eat);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	philo->fork = AVALIBLE;
	philo->fork = AVALIBLE;
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
	while (1)
	{
		if (philo_take_a_fork(philo))
			return ;
		if (philo_eat(philo))
			return ;
		philo_sleep(philo);
	}
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
