/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:05:45 by angelasoler       #+#    #+#             */
/*   Updated: 2023/07/22 20:11:59 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alert_dead(void *arg)
{
	long int		last_meal;
	struct timeval	time_now;
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&time_now, NULL);
	last_meal = (time_now.tv_usec - philo->last_meal.tv_usec) - \
				philo->args->t_eat;
	print_philo(philo, last_meal);
	if (last_meal <= 0)
		return (1);
	return (0);
}

int	verify_philos_state(t_philo *philo)
{
	if (philo->im_done)
		return (1);
	return (0);
}

int	ft_lstiter(t_list *lst, int (f)(void *))
{
	t_list	*aux;

	aux = lst;
	while (aux)
	{
		if (f(aux->philo))
			return (printf("philo %d starved\n", aux->philo->id));
		else
			if (verify_philos_state(aux->philo))
				return (0);
		aux = aux->next;
	}
	printf("circle linked list fail\n");
	exit(1);
	return (0);
}

const char* stateToString(t_state state) {
	switch (state) {
		case EAT:
			return "EAT";
		case THINK:
			return "THINK";
		case SLEEP:
			return "SLEEP";
		default:
			return "UNKNOWN";
	}
}

void	print_philo(t_philo *philo, long int last_meal)
{
	printf("Philo:\n");
	printf("  State: %s\n", stateToString(philo->state));
	printf("  ID: %d\n", philo->id);
	printf("  im_done: %d\n", philo->im_done);
	printf("last meal time is over? %s\n", last_meal  <= 0? "true":"false");
}
