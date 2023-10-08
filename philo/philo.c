/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:43 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 17:53:25 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dinner(t_dinner *dinner)
{
	t_list	*list;
	int		n_philos;

	n_philos = dinner->args.n_philos;
	dinner->philo = ft_calloc(sizeof(t_philo), n_philos);
	if (!dinner->philo)
		return (printf("philo malloc fail\n"));
	init_fork_mutex(dinner, n_philos);
	list = init_philos(dinner);
	if (!list)
		return (printf("list alloc fail\n"));
	init_threads(dinner, n_philos, list);
	return (0);
}

int	init_data(t_args *data, char *args[])
{
	if (verify_data(args))
		return (printf("invalid arguments\n"));
	data->n_philos = ft_atoi(args[1]);
	if (data->n_philos <= 0)
		return (printf("invalid arguments\n"));
	data->t_die = ft_atoi(args[2]);
	data->t_eat = ft_atoi(args[3]);
	data->t_sleep = ft_atoi(args[4]);
	if (data->n_must_eat)
		data->n_must_eat = ft_atoi(args[5]);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_dinner	*dinner;

	if (argc < 5 || argc > 6)
		return (printf("Wrong arguments\n"));
	dinner = ft_calloc(1, sizeof(t_dinner));
	if (!dinner)
		return (printf("calloc fail\n"));
	if (argc < 6)
		dinner->args.n_must_eat = FALSE;
	else
		dinner->args.n_must_eat = TRUE;
	if (init_data(&dinner->args, argv))
	{
		free(dinner);
		return (-1);
	}
	init_dinner(dinner);
	return (0);
}
