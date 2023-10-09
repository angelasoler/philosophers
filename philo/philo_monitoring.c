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

int	alert_dead(t_philo *philo)
{
	int	eat_or_die;
	int	last_meal_timer;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal_timer = (gettime_milisec_convertion() - philo->last_meal);
	eat_or_die = philo->args->t_die;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (last_meal_timer > eat_or_die)
	{
		pthread_mutex_lock(philo->alert_end_mutex);
		*philo->alert_end = TRUE;
		pthread_mutex_unlock(philo->alert_end_mutex);
		philo_print_log(philo, DIED);
		return (1);
	}
	return (0);
}

char	verify_philos_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->im_done_mutex);
	if (philo->im_done)
	{
		pthread_mutex_unlock(&philo->im_done_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->im_done_mutex);
	return (FALSE);
}

int	philo_everybodys_done(char **done_counter, int nphilo, t_philo *philo)
{
	int		i;
	int		cnt_true;
	char	*aux;

	i = 0;
	cnt_true = 0;
	aux = *done_counter;
	while (i < nphilo)
	{
		if (aux[i] == TRUE)
			cnt_true++;
		i++;
	}
	if (cnt_true == nphilo)
	{
		free(aux);
		pthread_mutex_lock(philo->alert_end_mutex);
		*philo->alert_end = TRUE;
		pthread_mutex_unlock(philo->alert_end_mutex);
		return (1);
	}
	return (0);
}

void	*ft_lstiter(void *lst)
{
	char	*done_counter;
	t_list	*aux;
	int		nphilos;
	int		i;

	aux = (t_list *)lst;
	nphilos = aux->philo->args->n_philos;
	done_counter = ft_calloc(nphilos + 1, sizeof(char));
	i = 0;
	while (aux)
	{
		if (alert_dead(aux->philo))
			free (done_counter);
		done_counter[i] = verify_philos_state(aux->philo);
		philo_everybodys_done(&done_counter, nphilos, aux->philo);
		if (*aux->philo->alert_end)
			return ((void *)0);
		aux = aux->next;
		i++;
		if (i == nphilos)
			i = 0;
	}
	printf("circle linked list fail\n");
	exit(1);
}
