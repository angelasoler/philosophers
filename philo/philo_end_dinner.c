/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_dinner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:19:18 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 11:34:33 by asoler           ###   ########.fr       */
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
		// pthread_mutex_destroy(&dinner->philo[id].fork_mutex);
		// if (pthread_mutex_destroy(&dinner->philo[id].fork_mutex))
			// return (printf("philo %d fork mutex destroy fails\n", (id + 1)));
		free_mutex(&dinner->philo[id]);
		id++;
	}
	pthread_mutex_destroy(&dinner->alert_end_mutex);
	pthread_mutex_destroy(&dinner->print_mutex);
	free(dinner->philo);
	free(dinner);
	return (0);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->philo);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*aux;
	t_list	*aux1;

	aux = *lst;
	aux1 = *lst;
	while (aux1)
	{
		aux->philo = NULL;
		aux1 = aux->next;
		free(aux);
		aux = aux1;
	}
	*lst = NULL;
}
