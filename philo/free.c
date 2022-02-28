/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 17:28:33 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/28 17:28:43 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	msg_and_free(t_philo *ph, t_data *d, char *str, int ret)
{
	printf("%s\n", str);
	free_all(ph, d);
	return (ret);
}

void	destroy_mutexes(t_philo *ph)
{
	int	i;

	pthread_mutex_destroy(&ph->d->mut_print);
	pthread_mutex_destroy(&ph->d->mut_protect);
	i = 0;
	while (i < ph->d->nrfilos)
	{
		pthread_mutex_destroy(&ph->d->mut_forks[i]);
		i++;
	}
}

void	join_threads(t_data data, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < data.nrfilos)
	{
		if (pthread_join(ph[i].thread, NULL) != 0)
			printf("Error joining a thread %d\n", i);
		i++;
	}
}

void	free_all(t_philo *ph, t_data *d)
{
	destroy_mutexes(ph);
	if (ph->d->mut_forks != NULL)
	{
		free(d->mut_forks);
		d->mut_forks = NULL;
	}
	if (ph != NULL)
	{
		free(ph);
		ph = NULL;
	}
}
