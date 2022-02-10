#include "newheader.h"


long long milisecs_passed(t_philo *ph)
{
	struct timeval	t;
	long long		milisecs;


	//pthread_mutex_lock(&ph->d->mutex_time);
	gettimeofday(&t, NULL);
	milisecs = t.tv_sec * 1000 + t.tv_usec / 1000;
	milisecs = milisecs - ph->d->startofsession;
	//pthread_mutex_lock(&ph->d->mutex_time);

	return (milisecs);
}


void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	pthread_mutex_lock(&ph->d->mutex_print);
	//printf("%lld %d %s\n", milisecs_passed(ph), ph->id + 1, str);
	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
	
	mspassed = time - ph->d->startofsession;
	
	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
	printf("%lld %d %s ... deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
	
	pthread_mutex_unlock(&ph->d->mutex_print);
}



void	mysleep(int milisecs, long long new_start)
{
	//long int	a;
	long int		time;
	long long int	deadline;
	struct			timeval t;

	//gettimeofday(&t, NULL);
	//deadline = (t.tv_sec * 1000 + t.tv_usec / 1000) + milisecs;
	//deadline = a + milisecs;
	deadline = new_start + milisecs;
	time = 0;
	while (time <= deadline)
	{
		usleep(50);
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
