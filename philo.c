/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:43 by asoler            #+#    #+#             */
/*   Updated: 2023/05/04 00:51:18 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dinner	dinner;

	ft_memset((void *)&dinner, 0, sizeof(dinner));
	if (argc < 5 || argc > 6)
		return (printf("Wrong arguments\n"));
	if (argc < 6)
		dinner.args.n_must_eat = FALSE;
	else
		dinner.args.n_must_eat = TRUE;
	if (init_data(&dinner.args, argv))
		return (-1);
	if (init_dinner(&dinner))
		return (printf("init philo fail\n"));
	end_dinner(&dinner);
	return (0);
}
