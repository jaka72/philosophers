#include "philo.h"

int	check_if_all_ate_nr_times(t_philo *f)
{
	int	i;
	
	i = 0;
	while (i < f->d->nrfilos)
	{
		if (f->d->new_times_eaten[i] < f->d->nr_times_to_eat)
			return (0);
		i++;
	}
	exit(0);
}


// void	mysleep(int milisecs)
// {
// 	long int	a;
// 	long int	b;
// 	long int	deadline;
// 	struct		timeval t;

// 	gettimeofday(&t, NULL);
// 	a = t.tv_sec * 1000000 + t.tv_usec;
// 	deadline = a + milisecs * 1000;
// 	b = 0;
// 	while (b <= deadline)
// 	{
// 		usleep(10);
// 		gettimeofday(&t, NULL);
// 		b = t.tv_sec * 1000000 + t.tv_usec;
// 	}
// }


// long int	milisecs_passed(t_philo *ph)
// {
// 	long int timestamp;
// 	long int a;
// 	struct timeval t;

// 	gettimeofday(&t, NULL);
// 	a = t.tv_sec * 1000000 + t.tv_usec;
// 	timestamp = (a - ph->d->time_start_of_session) / 1000;
// 	return (timestamp);
// }

void	mysleep(int milisecs)
{
	long int	a;
	long int	b;
	long int	deadline;
	struct		timeval t;

	gettimeofday(&t, NULL);
	a = t.tv_sec * 1000000 + t.tv_usec;
	deadline = a + milisecs * 1000;
	b = 0;
	while (b <= deadline)
	{
		usleep(10);
		gettimeofday(&t, NULL);
		b = t.tv_sec * 1000000 + t.tv_usec;
	}
}


long int	milisecs_passed(t_philo *ph)
{
	long int timestamp;
	long int a;
	struct timeval t;

	gettimeofday(&t, NULL);
	//a = t.tv_sec * 1000000 + t.tv_usec;
	a = t.tv_sec * 1000 + t.tv_usec / 1000;
	//timestamp = (a - ph->d->time_start_of_session) / 1000;
	timestamp = a - ph->d->time_start_of_session;
	return (timestamp);
}
