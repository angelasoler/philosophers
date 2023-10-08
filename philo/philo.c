/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:43 by asoler            #+#    #+#             */
/*   Updated: 2023/10/07 20:22:08 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dinner	*dinner;

	dinner = ft_calloc(1, sizeof(t_dinner));
	if (!dinner)
		return (printf("calloc fail\n"));
	if (argc < 5 || argc > 6)
		return (printf("Wrong arguments\n"));
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
	// end_dinner(dinner);
	return (0);
}
