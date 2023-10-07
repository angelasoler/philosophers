/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:11:07 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 10:07:38 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_args(t_args *data, const char *where)
{
	printf("------------ ARGS %s ---------\n", where);
	printf("n_philos = %d\n", data->n_philos);
	printf("t_die = %d\n", data->t_die);
	printf("t_eat = %d\n", data->t_eat);
	printf("t_sleep = %d\n", data->t_sleep);
	if (data->n_must_eat)
		printf("n_must_eat = %d\n", data->n_must_eat);
}

