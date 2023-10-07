/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 16:55:07 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_leaves_the_table(t_philo *philo)
{
	pthread_mutex_lock(&philo->alert_dead_mutex);
	if (*philo->alert_end)
	{
		pthread_mutex_unlock(&philo->alert_dead_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->alert_dead_mutex);
	return (FALSE);
}

int	philo_think(t_philo *philo)
{
	if (philo_leaves_the_table(philo))
		return (1);
	philo_print_log(philo, THINK);
	usleep(500);
	if (philo_leaves_the_table(philo))
		return (1);
	return (0);
}

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
		pthread_mutex_lock(&philo->fork_mutex);
		philo->fork = BUSY;
	}
	else
	{
		pthread_mutex_lock(&philo->neighbor->fork_mutex);
		philo->neighbor->fork = BUSY;
	}
	philo_print_log(philo, FORK);
	if (philo_leaves_the_table(philo) || philo->args->n_philos == 1)
	{
		if (!neighboor)
			pthread_mutex_unlock(&philo->fork_mutex);
		else
			pthread_mutex_unlock(&philo->neighbor->fork_mutex);
		return (1);
	}
	return (0);
}

int update_meals_counters(t_philo *philo)
{
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

int	philo_eat(t_philo *philo)
{
	philo_print_log(philo, EAT);
	milisec_sleep(philo->args->t_eat);
	philo->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->fork_mutex);
	philo->neighbor->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	return (update_meals_counters(philo));
}

void	pair_philos_wait(t_philo *philo)
{
	if (!(philo->id % 2))
		milisec_sleep(35);
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
			|| philo_take_a_fork(philo, neighboor)
			|| philo_take_a_fork(philo, !neighboor)
			|| philo_eat(philo)
			|| philo_sleep(philo))
			return ;
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
	return ((void *)0);
}
