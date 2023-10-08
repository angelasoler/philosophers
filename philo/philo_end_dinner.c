/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_dinner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:19:18 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 16:22:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_dinner(t_dinner *dinner)
{
	int	id;
	int	n_philos;

	id = 0;
	n_philos = dinner->args.n_philos;
	while (id < n_philos)
	{
		pthread_join(dinner->philo[id].philosopher, NULL);
		if (pthread_mutex_destroy(&dinner->philo[id].fork_mutex))
			return (printf("philo %d fork mutex destroy fails\n", (id + 1)));
		free_mutex(&dinner->philo[id]);
		id++;
	}
	pthread_mutex_destroy(&dinner->alert_end_mutex);
	pthread_mutex_destroy(&dinner->print_mutex);
	free(dinner->philo);
	free(dinner);
	return (0);
}

void	freelist(t_list *head)
{
	t_list	*current;
	t_list	*start;
	t_list	*next;

	current = head;
	start = head;
	while (current->next != start)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
}
