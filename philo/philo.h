/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelasoler <angelasoler@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:34 by asoler            #+#    #+#             */
/*   Updated: 2023/07/22 18:50:30 by angelasoler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0
# define PHILO_H

typedef struct timeval	t_now;

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
	int			n_must_eat;
}	t_args;

typedef struct s_philo
{
	pthread_t		philosopher;
	t_fork			fork;
	t_state			state;
	int				id;
	int				im_done;
	t_args			*args;
	pthread_mutex_t	fork_mutex;
	struct timeval	last_meal;
	struct s_philo	*neighbor;
}	t_philo;

typedef struct s_list
{
	t_philo			*philo;
	struct s_list	*next;
}	t_list;

typedef struct s_dinner
{
	t_args	args;
	t_philo	*philo;
	int		detach;
}	t_dinner;

int		alert_dead(void *arg);

t_list	*ft_lstlast(t_list *lst);
int		alloc_philo_list(t_list **main_list, t_philo *philo, int id);

int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

int		init_data(t_args *data, char *args[]);
int		init_philos(t_dinner *dinner);
int		init_dinner(t_dinner *dinner);
void	*join_meal(void *arg);
int		end_dinner(t_dinner *dinner);

#endif
