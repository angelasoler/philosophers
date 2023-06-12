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

typedef struct s_data
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_time_sleep;
}	t_data;

typedef struct s_philo
{
	pthread_t		philosopher;
	t_fork			fork;
	t_state			state;
	int				id;
	t_data			*data;
	pthread_mutex_t	fork_mutex;
	struct timeval	last_meal;
	struct s_philo	**neighbor;
}	t_philo;

typedef struct s_dinner
{
	t_philo			*philo;
}	t_dinner;

typedef struct s_main
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_time_sleep;
	t_dinner	dinner;
}	t_main;

int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

int		init_data(t_main *data, char *args[]);
int		init_philos(t_main	*data);
int		init_dinner(t_main *data);
void	*table(void *arg);
int		end_dinner(t_main *data);

#endif
