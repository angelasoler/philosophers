/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_log.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:13:05 by asoler            #+#    #+#             */
/*   Updated: 2023/10/03 00:37:53 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print_log(t_philo *philo, int state)
{
	t_now	time_now;

	gettimeofday(&time_now, NULL);
	pthread_mutex_lock(&philo->print_mutex);
	if (state == EAT)
		printf("%ld %d is eating\n", time_now.tv_usec, philo->id);
	else if (state == THINK)
		printf("%ld %d is thinking\n", time_now.tv_usec, philo->id);
	else if (state == SLEEP)
		printf("%ld %d is sleeping\n", time_now.tv_usec, philo->id);
	else if (state == FORK)
		printf("%ld %d has taken a fork\n", time_now.tv_usec, philo->id);
	else if (state == DIED)
		printf("%ld %d died\n", time_now.tv_usec, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
