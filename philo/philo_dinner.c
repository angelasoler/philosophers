/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 21:24:43 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	if (philo_leaves_the_table(philo))
		return (1);
	philo_print_log(philo, SLEEP);
	milisec_sleep(philo->args->t_sleep);
	if (philo_leaves_the_table(philo))
		return (1);
	return (0);
}

int	philo_take_a_fork(t_philo *philo, int neighboor)
{
	if (!neighboor)
	{
		if (pthread_mutex_lock(&philo->fork_mutex))
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(&philo->neighbor->fork_mutex))
			return (1);
	}
	if (philo_leaves_the_table(philo) || philo->args->n_philos == 1)
	{
		if (!neighboor)
			pthread_mutex_unlock(&philo->fork_mutex);
		else
			pthread_mutex_unlock(&philo->neighbor->fork_mutex);
		return (1);
	}
	philo_print_log(philo, FORK);
	return (0);
}

int	philo_eat(t_philo *philo, int neighboor)
{
	if (!philo_leaves_the_table(philo) && !philo_take_a_fork(philo, neighboor))
	{
		if (philo_take_a_fork(philo, !neighboor))
		{
			if (philo->id == 1)
				pthread_mutex_unlock(&philo->neighbor->fork_mutex);
			else
				pthread_mutex_unlock(&philo->fork_mutex);
			return (0);
		}
	}
	else
		return (0);
	if (!philo_leaves_the_table(philo))
	{
		update_meals_counters(philo);
		philo_print_log(philo, EAT);
		milisec_sleep(philo->args->t_eat);
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	if (philo_leaves_the_table(philo))
		return (1);
	return (0);
}

void	set_at_the_table(t_philo *philo)
{
	int	neighboor;

	if (philo->id == 1)
		neighboor = TRUE;
	else
		neighboor = FALSE;
	pair_philos_wait(philo);
	while (1)
	{
		if (philo_think(philo)
			|| philo_eat(philo, neighboor)
			|| philo_sleep(philo))
			return ;
	}
}

void	*join_meal(void	*arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	set_at_the_table(philo);
	return ((void *)0);
}
