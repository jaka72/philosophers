/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 17:29:15 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/28 17:29:16 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	has_died(t_philo *ph, long long current_time)
{
	pthread_mutex_lock(&ph->d->mut_protect);
	if (current_time > ph->deadline)
	{
		ph->d->hasdied = 1;
		pthread_mutex_unlock(&ph->d->mut_protect);
		pthread_mutex_lock(&ph->d->mut_print);
		printf("%lld %d died\n", current_time - ph->d->startofsession,
			ph->id + 1);
		pthread_mutex_unlock(&ph->d->mut_print);
		return (1);
	}
	pthread_mutex_unlock(&ph->d->mut_protect);
	pthread_mutex_lock(&ph->d->mut_protect);
	if (ph->d->mealsreached == 1)
	{
		pthread_mutex_unlock(&ph->d->mut_protect);
		return (1);
	}
	pthread_mutex_unlock(&ph->d->mut_protect);
	return (0);
}

int	timer(t_philo *philo)
{
	int					i;
	struct timeval		t;
	unsigned long long	current_time;
	t_philo				*ph;

	ph = philo;
	while (1)
	{
		i = 0;
		usleep(1000);
		while (i < ph->d->nrfilos)
		{
			gettimeofday(&t, NULL);
			current_time = t.tv_sec * 1000 + t.tv_usec / 1000;
			if (has_died(&ph[i], current_time) == 1)
				return (0);
			i++;
		}
	}
	return (0);
}
