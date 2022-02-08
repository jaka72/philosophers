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
	unsigned long long	old;
	unsigned long long	new;
	unsigned long long	deadline;
	struct		timeval time;

	gettimeofday(&time, NULL);
	old = time.tv_sec * 1000000 + time.tv_usec;
	deadline = old + milisecs * 1000;
	new = 0;
	while (new <= deadline)
	{
		usleep(10);
		gettimeofday(&time, NULL);
		new = time.tv_sec * 1000000 + time.tv_usec;
	}
}


// unsigned long	milisecs_passed(t_philo *ph)
// {
// 	unsigned long 		timestamp;
// 	unsigned long long	newtime; // maybe it is enough just long int ???
// 	struct timeval		t;



// 	//pthread_mutex_lock(&ph->mutex_time);

// 	gettimeofday(&t, NULL);
// 	//a = t.tv_sec * 1000000 + t.tv_usec;
// 	newtime = t.tv_sec * 1000 + t.tv_usec / 1000;
// 	//timestamp = (a - ph->d->time_start_of_session) / 1000;
// 	//timestamp = newtime - ph->d->time_start_of_session;
// 	timestamp = newtime - ph->startofsession;
	
// 	printf(" .......   newtime:                 %lld\n", newtime);
// 	printf(" .......   ph->start_of_session:    %lld\n", ph->startofsession);
// 	printf(" ....... timestamp:                %ld\n", timestamp);
	
	
// 	//pthread_mutex_unlock(&ph->mutex_time);

// 	return (timestamp);
// }


unsigned long	milisecs_passed(t_philo *ph)
{
	unsigned long 		timestamp;
	unsigned long long	newtime; // maybe it is enough just long int ???
	struct timeval		t;


	//pthread_mutex_lock(&ph->mutex_time);

	gettimeofday(&t, NULL);
	//pthread_mutex_unlock(&ph->mutex_time);

	//a = t.tv_sec * 1000000 + t.tv_usec;
	newtime = t.tv_sec * 1000 + t.tv_usec / 1000;
	//timestamp = (a - ph->d->time_start_of_session) / 1000;
	//timestamp = newtime - ph->d->time_start_of_session;
	timestamp = newtime - ph->d->startofsession;
	
	// printf(" ....... newtime:             %lld\n", newtime);
	// printf(" ....... start_of_session:    %lld\n", startofsession);
	// printf(" ....... timestamp:           %ld\n", timestamp);
	
	

	return (timestamp);
}
