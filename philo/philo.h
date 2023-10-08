/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 00:48:34 by asoler            #+#    #+#             */
/*   Updated: 2023/10/08 17:54:14 by asoler           ###   ########.fr       */
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
	SLEEP,
	FORK,
	DIED
}	t_state;

typedef enum s_fork
{
	AVALIBLE,
	BUSY
}	t_fork;

typedef struct s_args
{
	int		n_philos;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		n_must_eat;
}	t_args;

typedef struct s_philo
{
	int				*alert_end;
	pthread_t		philosopher;
	t_fork			fork;
	t_state			state;
	int				id;
	int				im_done;
	int				meal_counter;
	t_args			*args;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	im_done_mutex;
	pthread_mutex_t	*alert_end_mutex;
	int				last_meal;
	struct s_philo	*neighbor;
}	t_philo;

typedef struct s_list
{
	t_philo			*philo;
	struct s_list	*next;
}	t_list;

typedef struct s_dinner
{
	pthread_mutex_t	alert_end_mutex;
	pthread_mutex_t	print_mutex;
	int				alert_end;
	t_args			args;
	t_philo			*philo;
	pthread_t		monitor_thread;
}	t_dinner;

t_list	*ft_lstlast(t_list *lst);
int		alloc_philo_list(t_list **main_list, t_philo *philo, int *id);

int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

int		init_data(t_args *data, char *args[]);
t_list	*init_philos(t_dinner *dinner);
int		init_dinner(t_dinner *dinner);
void	*join_meal(void *arg);
int		end_dinner(t_dinner *dinner);
int		create_philosopher(t_philo *philo, t_philo *neighbor, t_dinner *dinner);
int		create_threads(int n_philos, t_philo *philo);
t_list	*init_philos(t_dinner *dinner);
int		init_fork_mutex(t_dinner *dinner, int n_philos);
int		init_threads(t_dinner *dinner, int n_philo, t_list	*list);

int		alert_dead(t_philo *philo);
void	*ft_lstiter(void *lst);
int		verify_data(char **args);

int		philo_init_mutex(t_philo *philo);
int		free_mutex(t_philo *philo);
void	philo_print_log(t_philo *philo, int state);
long	gettime_milisec_convertion(void);
void	milisec_sleep(long duration);

void	print_args(t_args *data, const char *where);
void	print_philo(t_philo *philo, long int last_meal);

void	pair_philos_wait(t_philo *philo);
int		update_meals_counters(t_philo *philo);
int		philo_leaves_the_table(t_philo *philo);
int		philo_think(t_philo *philo);

void	freelist(t_list *head);

#endif
