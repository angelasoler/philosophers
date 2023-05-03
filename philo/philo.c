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
	t_main	data;

	if (argc < 5 || argc > 6)
		return (printf("Worng arguments\n"));
	if (argc < 6)
		data.n_time_sleep = FALSE;
	else
		data.n_time_sleep = TRUE;
	if (init_data(&data, argv))
		return (-1);
	if (init_dinner(&data))
		return (printf("init philo fail\n"));
	end_dinner(&data);
	return (0);
}
