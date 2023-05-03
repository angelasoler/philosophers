#ifndef PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# define TRUE 1
# define FALSE 0
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
	pthread_mutex_t	dinner;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_dinner;


typedef struct s_main
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_time_sleep;
	int			actual_id;
	t_dinner	dinner;
}	t_main;

int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);

int		init_data(t_main *data, char *args[]);
int		init_philos(t_main	*data);
int		init_dinner(t_main *data);
void	*table(void *arg);
int		end_dinner(t_main *data);

#endif
