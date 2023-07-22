/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:45:14 by angelasoler       #+#    #+#             */
/*   Updated: 2023/07/22 19:45:44 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

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

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->philo);
	free(lst);
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
