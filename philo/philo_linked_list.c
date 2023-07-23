/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:45:14 by asoler       #+#    #+#             */
/*   Updated: 2023/07/22 23:20:42 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*back;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	back = ft_lstlast(*lst);
	back->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	aux = lst;
	while (aux)
	{
		if (!aux->next)
			return (aux);
		aux = aux->next;
	}
	return (aux);
}

t_list	*ft_lstnew(void	*philo)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	if (!result)
		return (0);
	result->philo = philo;
	result->next = NULL;
	return (result);
}

int	alloc_philo_list(t_list **main_list, t_philo *philo, int id)
{
	int		n_philos;
	t_list	*list;
	t_list	*last;

	list = ft_lstnew((void *)philo);
	n_philos = philo->args->n_philos;
	if (main_list)
		ft_lstadd_back(&(*main_list), list);
	if (id == (n_philos - 1))
	{
		last = ft_lstlast(*main_list);
		last->next = *main_list;
	}
	else if (!id)
		*main_list = list;
	return (0);
}
