/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_log.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:13:05 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 11:29:02 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime_milisec_convertion(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL))
		return (printf("Failed getting time\n"));
	return ((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000));
}

void	milisec_sleep(long duration)
{
	long	init_timer;

	init_timer = gettime_milisec_convertion();
	while ((gettime_milisec_convertion() - init_timer) < duration)
		usleep(10);
}

void	philo_print_log(t_philo *philo, int state)
{
	int	time_now;

	time_now = gettime_milisec_convertion();
	pthread_mutex_lock(&philo->print_mutex);
	if (state == EAT)
		printf("%d %d is eating\n", time_now, philo->id);
	else if (state == THINK)
		printf("%d %d is thinking\n", time_now, philo->id);
	else if (state == SLEEP)
		printf("%d %d is sleeping\n", time_now, philo->id);
	else if (state == FORK)
		printf("%d %d has taken a fork\n", time_now, philo->id);
	else if (state == DIED)
		printf("%d %d died\n", time_now, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
