/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/10/04 20:47:20 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_leaves_the_table(t_philo *philo)
{
	return (philo->args->alert_dead); //alert end?
}

void	philo_think(t_philo *philo)
{
	philo_print_log(philo, THINK);
	usleep(500);
}

void	philo_take_first_fork(t_philo *philo)
{
	int		fork;

	if (philo->id == 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			philo->neighbor->fork = BUSY;
			// pthread_mutex_unlock(&philo->neighbor->fork_mutex);
			philo_print_log(philo, FORK);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			philo->fork = BUSY;
			// pthread_mutex_unlock(&philo->fork_mutex);
			philo_print_log(philo, FORK);
		}
	}
}

void	philo_take_second_fork(t_philo *philo)
{
	int		fork;

	if (philo->id != 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			philo->neighbor->fork = BUSY;
			// pthread_mutex_unlock(&philo->neighbor->fork_mutex);
			philo_print_log(philo, FORK);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			philo->fork = BUSY;
			// pthread_mutex_unlock(&philo->fork_mutex);
			philo_print_log(philo, FORK);
		}
	}
}

int	philo_eat(t_philo *philo)
{
	philo_print_log(philo, EAT);
	usleep(philo->args->t_eat);
	
	// pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->fork_mutex);

	// pthread_mutex_lock(&philo->neighbor->fork_mutex);
	philo->neighbor->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = gettime_milisec_convertion();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (philo->args->n_must_eat)
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->args->n_must_eat)
		{
			pthread_mutex_lock(&philo->im_done_mutex);
			philo->im_done = TRUE;
			pthread_mutex_unlock(&philo->im_done_mutex);
			return (1);
		}
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	philo_print_log(philo, SLEEP);
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
