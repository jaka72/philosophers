#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define COLOR true

typedef struct s_data
{
	int				nrfilos;
	pthread_mutex_t	*fork_mutex;
	long int		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		time_start_of_session;
	int				nr_times_to_eat;
	long int		*time_started_eating;
	long int		*deadlines;
	int				*old_times_eaten;
	int				*new_times_eaten;
} t_data;

typedef struct s_philosopher
{
	int				philo_id;
	t_data			*d;
	struct timeval	start;
	pthread_t		timer_thread;
} t_philo;

int			check_and_save_arguments(int argc, char *argv[], t_data *d);
int			make_arrays_and_philos(t_data *d);
void		mysleep(int milisecs);
long int	milisecs_passed(t_philo *ph);
// char *colors(int i);
// char *choose_color(t_filo *f);

# define BLKB  "\e[40m"
# define HYEL  "\e[0;93m"
# define HGRN  "\e[0;92m"
# define HWHT  "\e[0;97m"
# define YEL   "\e[0;33m"
# define RED   "\x1B[31m"
# define REDB  "\e[41m"
# define GRN   "\x1B[32m"
# define LGRN  "\e[0;92m"
# define BLUBH "\e[44m"
# define BLUB  "\e[1;36m"
# define BLU   "\e[0;34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RES   "\x1B[0m"

#endif
