/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:12 by asoler            #+#    #+#             */
/*   Updated: 2023/05/04 00:52:59 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	power(const char n, int len)
{
	int	number;

	number = n - 48;
	if (len == 0)
		return (number);
	while (len > 0)
	{
		number *= 10;
		len--;
	}
	return (number);
}

static int	ft_result(const char *n, int len)
{
	int	result;

	result = 0;
	while (len > 0)
	{
		len--;
		result += power(*n, len);
		n++;
	}
	return (result);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long int	result;
	int			b;

	i = 0;
	b = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		b = 1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	result = ft_result(nptr, i);
	if (b)
		result *= -1;
	return ((int)result);
}
