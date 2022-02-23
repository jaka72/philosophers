/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:15:04 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/22 15:15:05 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	print_and_return(int code, char *msg)
{
	printf("%s", msg);
	return (code);
}

void	mysleep(int milisecs)
{
	long int		current;
	long int		deadline;
	struct timeval	t;

	gettimeofday(&t, NULL);
	deadline = (t.tv_sec * 1000 + t.tv_usec / 1000) + milisecs;
	current = 0;
	while (current <= deadline)
	{
		usleep(500);
		gettimeofday(&t, NULL);
		current = t.tv_sec * 1000 + t.tv_usec / 1000;
	}
}

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	mspassed = time - ph->d->startofsession;
	pthread_mutex_lock(&ph->d->mutex_death);
	if (ph->d->hasdied != 1 && ph->d->mealsreached != 1)
		printf("%lld %d %s\n", mspassed, ph->id + 1, str);
	pthread_mutex_unlock(&ph->d->mutex_death);
}
