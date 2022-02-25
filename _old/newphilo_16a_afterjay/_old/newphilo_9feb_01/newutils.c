#include "newheader.h"


long long milisecs_passed(t_philo *ph)
{
	struct timeval	t;
	long long		milisecs;

	//pthread_mutex_lock(&ph->d->mutex_time);  // it all stops with this
	gettimeofday(&t, NULL);
	//pthread_mutex_unlock(&ph->d->mutex_time);

	milisecs = t.tv_sec * 1000 + t.tv_usec / 1000;
	milisecs = milisecs - ph->d->startofsession;


	return (milisecs);
}


long long get_time(t_philo *ph)
{
	struct timeval t;
	long long time;

	pthread_mutex_lock(&ph->d->mutex_time); // is this necessary ???
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(&ph->d->mutex_time);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}




void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	pthread_mutex_lock(&ph->d->mutex_print);
	
	mspassed = time - ph->d->startofsession;
	
	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
	//printf("%lld %d %s ... deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
	//printf("%lld %d %s\n", mspassed, ph->id, str);
	//printf("%lld %d %s  ...  deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
	printf("%lld %d %s\n", mspassed, ph->id, str);
	
	pthread_mutex_unlock(&ph->d->mutex_print);
}



void	mysleep(int milisecs, long long starttime)
{
	//long int	a;
	long int	time;
	long long	deadline;
	struct		timeval t;

	//gettimeofday(&t, NULL);
	//deadline = (t.tv_sec * 1000 + t.tv_usec / 1000) + milisecs;
	deadline = starttime + milisecs;
	//deadline = deadline + milisecs;
	//deadline = new_start + milisecs;
	time = 0;
	while (time <= deadline)
	{
		usleep(500);
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000 + t.tv_usec / 1000;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


void	free_all(t_philo *ph) // HERE PROBABLY NEEDED PROTECTION FROM DOUBLE FREE !!
{
	int	i;

	pthread_mutex_destroy(&ph->d->mutex_time);
	pthread_mutex_destroy(&ph->d->mutex_print);
	i = 0;
	while (i < ph->d->nrfilos)
	{
		pthread_mutex_unlock(&ph->d->mutex_spoon[i]);
		pthread_mutex_destroy(&ph->d->mutex_spoon[i]);
		i++;
	}
	free(ph->d->mutex_spoon);
	free(ph->d);
	free(ph);
}
