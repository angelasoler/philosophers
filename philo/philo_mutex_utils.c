/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:52:29 by asoler            #+#    #+#             */
/*   Updated: 2023/09/27 21:52:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->fork_mutex, NULL) ||
		pthread_mutex_init(&philo->last_meal_mutex, NULL) ||
		pthread_mutex_init(&philo->im_done_mutex, NULL))
		return (1);
	return (0);
}