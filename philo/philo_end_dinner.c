/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:18:51 by angelasoler       #+#    #+#             */
/*   Updated: 2023/07/22 20:08:52 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_dinner(t_dinner *dinner)
{
	int	id;
	int	*thread_ret;
	int	n_philos;

	id = 0;
	n_philos = dinner->args.n_philos;
	thread_ret = NULL;
	while (id < n_philos)
	{
		pthread_mutex_destroy(&dinner->philo[id].fork_mutex);
		if (dinner->detach)
			pthread_detach(dinner->philo[id].philosopher);
		else
			pthread_join(dinner->philo[id].philosopher, (void **)&thread_ret);
		if (thread_ret)
		{
			printf("Philo %d leaves the room\n", *thread_ret);
			free(thread_ret);
		}
		id++;
	}
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
