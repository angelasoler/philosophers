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

int	alert_dead(void *arg)
{
	long int		last_meal;
	struct timeval	time_now;
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&time_now, NULL);
	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = (time_now.tv_usec - philo->last_meal.tv_usec) - \
				philo->args->t_eat;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	// print_philo(philo, last_meal);
	if (last_meal <= 0)
		return (1);
	return (0);
}

int	verify_philos_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->im_done_mutex);
	if (philo->im_done)
	{
		pthread_mutex_unlock(&philo->im_done_mutex);
		return (1);

	}
	pthread_mutex_unlock(&philo->im_done_mutex);
	return (0);
}

int	philo_everybody_done(char *done_counter, int nphilo)
{
	int	i;
	int	cnt_true;

	i = 0;
	cnt_true = 0;
	while (i < nphilo)
	{
		if (done_counter[i] == TRUE)
			cnt_true++;
		i++;
	}
	if (cnt_true == nphilo)
		return (1);
	return (0);
}

int	ft_lstiter(t_list *lst, int (f)(void *))
{
	t_list			*aux;
	struct timeval	starve_timer;
	static char		*done_counter;

	aux = lst;
	done_counter = calloc(aux->philo->args->n_philos, sizeof(char));
	while (aux)
	{
		if (f(aux->philo))
		{
			gettimeofday(&starve_timer, NULL);
			return (printf("%ld %d died\n", starve_timer.tv_usec, aux->philo->id));
		}
		else
		{
			if (verify_philos_state(aux->philo))
				done_counter[aux->philo->id - 1] = TRUE;
		}
		if (philo_everybody_done(done_counter, aux->philo->args->n_philos))
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
	printf("  meal_counter: %d\n", philo->meal_counter);
	printf("  Im_done: %d\n", philo->im_done);
	if (last_meal <= 0)
		printf("  Starved: %s\n", "true");
	else
		printf("  Starved: %s\n", "false");
}
