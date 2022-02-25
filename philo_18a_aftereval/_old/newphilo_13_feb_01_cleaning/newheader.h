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
	int					max_meals_per_philo;
	int					count_meals;
	unsigned long long	startofsession;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		*mutex_forks;

	int					track_malloc[3];

}	t_data;


typedef struct s_philosopher
{
	t_data				*d;
	int					id;
	unsigned long long	new_start_time;
	long long			deadline;
	//int					times_ate;
	int					error;
	pthread_t			thread;

}	t_philo;


t_data		*check_and_store_arguments(int argc, char **argv);
void		mysleep(int milisecs, long long time);
int			ft_isdigit(int c);
long long	milisecs_passed(t_philo *ph);
void		message(t_philo *ph, char *str, unsigned long long time);
void		message_forkid(t_philo *ph, char *str, unsigned long long time, int id);

void		free_all(t_philo *ph, t_data *d);
int			timer(t_philo *ph);
long long	get_time(t_philo *ph);
int			error_and_free(t_philo *ph, t_data *d, char *str, int ret);

//int			has_died(t_philo *ph, long long current_time, long long new_start);




#endif