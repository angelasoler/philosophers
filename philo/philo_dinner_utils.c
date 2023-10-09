/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:11:46 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 20:59:14 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pair_philos_wait(t_philo *philo)
{
	if (!(philo->id % 2))
		milisec_sleep(35);
}

int	update_meals_counters(t_philo *philo)
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
		}
	}
	return (0);
}

int	philo_leaves_the_table(t_philo *philo)
{
	pthread_mutex_lock(philo->alert_end_mutex);
	if (*philo->alert_end)
	{
		pthread_mutex_unlock(philo->alert_end_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->alert_end_mutex);
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
