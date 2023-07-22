/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:43 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 09:06:31 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dinner	*dinner;

	dinner = ft_calloc(1, sizeof(dinner));
	// dinner->args = ft_calloc(1, sizeof(dinner->args));
	if (argc < 5 || argc > 6)
		return (printf("Wrong arguments\n"));
	if (argc < 6)
		dinner->args.n_must_eat = FALSE;
	else
		dinner->args.n_must_eat = TRUE;
	if (init_data(&dinner->args, argv))
		return (-1);
	if (init_dinner(dinner))
		return (printf("init philo fail\n"));
	end_dinner(dinner);
	return (0);
}
