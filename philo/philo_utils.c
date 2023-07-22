/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lib_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:59 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 20:12:32 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_data(char **args)
{
	int	col;
	int	row;

	row = 1;
	while (args[row])
	{
		col = 0;
		while (args[row][col])
		{
			if (!ft_isdigit(args[row][col]))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = (char *) s;
	while (i < n)
	{
		s1[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*result;

	i = 0;
	result = (char *)s;
	while (i < n)
	{
		result[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*x;

	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	x = malloc(size * nmemb);
	if (!x)
		return (NULL);
	ft_bzero(x, (size * nmemb));
	return (x);
}
