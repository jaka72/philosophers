#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_data
{
	int					nrfilos;
	unsigned long long	time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals_per_philo;
	int					count_meals;
	long long			startofsession;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		*mutex_forks;
}	t_data;

typedef struct s_philosopher
{
	t_data				*d;
	int					id;
	unsigned long long	new_start_time;
	long long			deadline;
	pthread_t			thread;

}	t_philo;

t_data		*check_and_store_arguments(int argc, char **argv);
int			ft_isdigit(int c);
void		message(t_philo *ph, char *str, unsigned long long time);
void		message_forkid(t_philo *ph, char *str, unsigned long long time,
				int id);
void		free_all(t_philo *ph, t_data *d);
void		*start_philo(void *philo);
int			timer(t_philo *ph, t_data *d);
long long	get_time(t_philo *ph);
int			msg_and_free(t_philo *ph, t_data *d, char *str, int ret);

#endif
