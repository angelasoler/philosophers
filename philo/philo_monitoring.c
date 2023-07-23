/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:05:45 by asoler       #+#    #+#             */
/*   Updated: 2023/07/22 23:20:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// print_philo(philo, last_meal);
int	alert_dead(void *arg)
{
	long int		last_meal;
	struct timeval	time_now;
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&time_now, NULL);
	last_meal = (time_now.tv_usec - philo->last_meal.tv_usec) - \
				philo->args->t_eat;
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

char	*state_to_string(t_state state)
{
	if (state == EAT)
		return ("EAT");
	else if (state == THINK)
		return ("THINK");
	else if (state == SLEEP)
		return ("SLEEP");
	return ("NULL");
}

void	print_philo(t_philo *philo, long int last_meal)
{
	printf("Philo:\n");
	printf("  State: %s\n", state_to_string(philo->state));
	printf("  ID: %d\n", philo->id);
	printf("  Im_done: %d\n", philo->im_done);
	if (last_meal <= 0)
		printf("  Starved: %s\n", "true");
	else
		printf("  Starved: %s\n", "false");
}