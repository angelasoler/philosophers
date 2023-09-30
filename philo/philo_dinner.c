/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/09/30 13:52:37 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	t_now	time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is thinking\n", time_now.tv_usec, philo->id);
	usleep(500);
}

void	philo_take_first_fork(t_philo *philo)
{
	int		fork;
	t_now	time_now;

	if (philo->id == 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			gettimeofday(&time_now, NULL);
			printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
			philo->neighbor->fork = BUSY;
			pthread_mutex_unlock(&philo->neighbor->fork_mutex);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			gettimeofday(&time_now, NULL);
			printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
			philo->fork = BUSY;
			pthread_mutex_unlock(&philo->fork_mutex);
		}
	}
}

void	philo_take_second_fork(t_philo *philo)
{
	int		fork;
	t_now	time_now;

	//ter um delay para o programa trocar entre threads
	//ver se printf é thread safe e se o hellgrind nao reclama
	if (philo->id != 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			gettimeofday(&time_now, NULL);
			printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
			philo->neighbor->fork = BUSY;
			pthread_mutex_unlock(&philo->neighbor->fork_mutex);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			gettimeofday(&time_now, NULL);
			printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
			philo->fork = BUSY;
			pthread_mutex_unlock(&philo->fork_mutex);
		}
	}
}

int	philo_eat(t_philo *philo)
{
	t_now		time_now;

	gettimeofday(&time_now, NULL);
	printf("%ld %d is eating\n", time_now.tv_usec, philo->id);
	usleep(philo->args->t_eat);
	
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->fork_mutex);

	pthread_mutex_lock(&philo->neighbor->fork_mutex);
	philo->neighbor->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (philo->args->n_must_eat)
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->args->n_must_eat)
		{
			pthread_mutex_lock(&philo->im_done_mutex);
			philo->im_done = 1;
			pthread_mutex_unlock(&philo->im_done_mutex);
			print_philo(philo, 0);
			return (1);
		}
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
		philo_take_first_fork(philo);
		philo_take_second_fork(philo);
		if (philo_eat(philo))
			return ;
		philo_sleep(philo);
		philo_think(philo);
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
	pthread_exit((void *)ret);
	return ((void *)0);
}
