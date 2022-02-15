#include "header.h"

long long	get_time(t_philo *ph)
{
	struct timeval	t;
	long long		time;

	pthread_mutex_lock(&ph->d->mutex_time);
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(&ph->d->mutex_time);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

int	msg_and_free(t_philo *ph, t_data *d, char *str, int ret)
{
	printf("%s\n", str);
	free_all(ph, d);
	return (ret);
}

void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	mspassed = time - ph->d->startofsession;
	printf("%lld %d %s\n", mspassed, ph->id + 1, str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
