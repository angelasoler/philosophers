/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:49:14 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 14:13:50 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_leaves_the_table(t_philo *philo)
{
	// pthread_mutex_lock()
	if (*philo->alert_end)
	{
		// pthread_mutex_unlock()
		return (TRUE);
	}
	return (FALSE);
}

void	philo_think(t_philo *philo)
{
	philo_print_log(philo, THINK);
	usleep(500);
}

void	philo_take_first_fork(t_philo *philo)
{
	int		fork;

	if (philo->id == 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			philo->neighbor->fork = BUSY;
			philo_print_log(philo, FORK);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			philo->fork = BUSY;
			philo_print_log(philo, FORK);
		}
	}
}

void	philo_take_second_fork(t_philo *philo)
{
	int		fork;

	if (philo->id != 1)
	{
		while (philo->neighbor->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->neighbor->fork_mutex);
		if (!fork)
		{
			philo->neighbor->fork = BUSY;
			philo_print_log(philo, FORK);
		}
	}
	else
	{
		while (philo->fork == BUSY)
			continue ;
		fork = pthread_mutex_lock(&philo->fork_mutex);
		if (!fork)
		{
			philo->fork = BUSY;
			philo_print_log(philo, FORK);
		}
	}
}

int	philo_eat(t_philo *philo)
{
	philo_print_log(philo, EAT);
	milisec_sleep(philo->args->t_eat);
	
	philo->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->fork_mutex);

	philo->neighbor->fork = AVALIBLE;
	pthread_mutex_unlock(&philo->neighbor->fork_mutex);
	
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = gettime_milisec_convertion();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (philo->args->n_must_eat)
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->args->n_must_eat)
		{
			pthread_mutex_lock(&philo->im_done_mutex);
			philo->im_done = TRUE;
			pthread_mutex_unlock(&philo->im_done_mutex);
			return (1);
		}
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	philo_print_log(philo, SLEEP);
	milisec_sleep(philo->args->t_sleep);
}

void	pair_philos_wait(t_philo *philo)
{
	if (!(philo->id % 2))
		milisec_sleep(35);
}

void	set_at_the_table(t_philo *philo)
{
	pair_philos_wait(philo);
	while (1)
	{
		philo_think(philo);
		if (philo_leaves_the_table(philo))
			return ;
		//tratameto para 1 philo só
		// if (philo->args->n_philos == 1)
		// {
		// 	philo_take_second_fork(philo);
		// 	while (!philo_leaves_the_table(philo))
		// 		usleep(10);
		// 	philo->fork = AVALIBLE;
		// 	pthread_mutex_unlock(&philo->fork_mutex);
		// 	return ;
		// }
		/////////////
		philo_take_first_fork(philo);
		// if (philo_leaves_the_table(philo))
		// {
		// 	//unlock and leave
		// 	return ;
		// }
		philo_take_second_fork(philo);
		// if (philo_leaves_the_table(philo))
		// {
		// 	//unlock and leave
		// 	return ;
		// }
		if (philo_eat(philo))
			return ;
		// if (philo_leaves_the_table(philo))
		// 	return ;
		philo_sleep(philo);
	}
}

void	*join_meal(void	*arg)
{
	int			*ret;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ret = ft_calloc(sizeof(int), 1);
	*ret = philo->id;
	set_at_the_table(philo);
	return ((void *)0);
}
