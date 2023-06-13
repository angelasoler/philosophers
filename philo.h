/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:34 by asoler            #+#    #+#             */
/*   Updated: 2023/05/04 00:53:11 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0
# define PHILO_H

typedef enum s_state
{
	EAT,
	THINK,
	SLEEP
}	t_state;

typedef enum s_fork
{
	AVALIBLE,
	BUSY
}	t_fork;

typedef struct s_args
{
	int			n_philos;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_time_sleep;
}	t_args;

typedef struct s_philo
{
	pthread_t		philosopher;
	t_fork			fork;
	t_state			state;
	int				id;
	t_args			*args;
	pthread_mutex_t	fork_mutex;
	struct timeval	last_meal;
	struct s_philo	*neighbor;
}	t_philo;

typedef struct s_dinner
{
	t_args	args;
	t_philo	*philo;
}	t_dinner;

int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

int		init_data(t_args *data, char *args[]);
int		init_philos(t_dinner *dinner);
int		init_dinner(t_dinner *dinner);
void	*table(void *arg);
int		end_dinner(t_dinner *dinner);

#endif
