#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_data
{
	int					nrfilos;
	unsigned long long	time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nr_times_to_eat;
	unsigned long long	startofsession;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		*mutex_spoon;
}	t_data;


typedef struct s_philosopher
{
	t_data				*d;
	int					id;
	unsigned long long	new_start_time;
	unsigned long long	deadline;
	pthread_t			thread;
}	t_philo;

t_data		*check_and_save_arguments(int argc, char *argv[]);
void		mysleep(int milisecs, long long new_start);
int			ft_isdigit(int c);
long long	milisecs_passed(t_philo *ph);
void		message(t_philo *ph, char *str, unsigned long long time);
void		free_all(t_philo *ph);




#endif