/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:52:29 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 19:25:23 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->fork_mutex, NULL) ||
		pthread_mutex_init(&philo->print_mutex, NULL) ||
		pthread_mutex_init(&philo->last_meal_mutex, NULL) ||
		pthread_mutex_init(&philo->im_done_mutex, NULL))
		return (printf("mutex init fails\n"));
	return (0);
}

int	free_mutex(t_philo *philo)
{
	if (pthread_mutex_destroy(&philo->fork_mutex) ||
		pthread_mutex_destroy(&philo->print_mutex) ||
		pthread_mutex_destroy(&philo->last_meal_mutex) ||
		pthread_mutex_destroy(&philo->im_done_mutex))
			return (printf("mutex destroy fails at philo %d\n", philo->id));
	return (0);
}
