#ifndef PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define PHILO_H

typedef enum s_state
{
	EAT,
	THINK,
	SLEEP
}	t_state;

typedef struct s_philo
{
	pthread_t	philosopher;
	int			state;
	int			id;
}	t_philo;

typedef struct s_dinner
{
	pthread_mutex	dinner;
	pthread_mutex	*fork;
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

#endif
