#include "newheader.h"

// MAYBE NOT USED ??????
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
	struct timeval	t;
	long long		time;

	pthread_mutex_lock(&ph->d->mutex_time); // is this necessary ???
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(&ph->d->mutex_time);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

// void	message_forkid(t_philo *ph, char *str, unsigned long long time, int id)
// {
// 	unsigned long long	mspassed;
// 	pthread_mutex_lock(&ph->d->mutex_print);
// 	mspassed = time - ph->d->startofsession;
// 	//printf("%lld %d %s ... deadline %lld\n", milisecs_passed(ph), ph->id + 1, str, milisecs_passed(ph) + ph->d->time_to_die);
// 	//printf("%lld %d %s ... deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
// 	//printf("%lld %d %s\n", mspassed, ph->id, str);
// 	//printf("%lld %d %s  ...  deadline %lld\n", mspassed, ph->id, str, mspassed + ph->d->time_to_die);
// 	printf("%lld %d %s, %d\n", mspassed, ph->id, str, id);
// 	pthread_mutex_unlock(&ph->d->mutex_print);
// }

void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

//	pthread_mutex_lock(&ph->d->mutex_print);
	mspassed = time - ph->d->startofsession;
	printf("%lld %d %s\n", mspassed, ph->id + 1, str);
//	pthread_mutex_unlock(&ph->d->mutex_print);
}

// NOT USED ??????
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

int	error_and_free(t_philo *ph, t_data *d, char *str, int ret)
{
	printf("%s\n", str);
	free_all(ph, d);
	return (ret);
}

void	free_all(t_philo *ph, t_data *d) // HERE PROBABLY NEEDED PROTECTION FROM DOUBLE FREE !!
{
//	int	i;

	printf("trackmalloc[1] %d\n", d->track_malloc[1]);

// MAYBE THIS IS NOT NEEDED, BECAUSE IT DOES NOT CAUSE ANY 
//   ISSUES IF IT IS NOT DESTROYED
//	pthread_mutex_destroy(&ph->d->mutex_time);
//	pthread_mutex_destroy(&ph->d->mutex_print);
	// i = 0;
	// while (i < ph->d->nrfilos)
	// {
	// 	pthread_mutex_unlock(&ph->d->mutex_forks[i]);
	// 	pthread_mutex_destroy(&ph->d->mutex_forks[i]);
	// 	i++;
	// }


//	if (ph->d->mutex_forks != NULL)
	if (d->track_malloc[0] == 1)
	{
		printf("free forks\n");
		printf("free ph->d->mutext_forks %p\n", d->mutex_forks);
		free(d->mutex_forks);
		d->mutex_forks = NULL;
	}
	//if (ph->d != NULL)
	if (d->track_malloc[1] == 1)
	{
		printf("free d\n");
		free(d);
		d = NULL;
	}
	if (ph != NULL)
	{
		printf("free ph\n");
		free(ph);
		ph = NULL;
	}
}
