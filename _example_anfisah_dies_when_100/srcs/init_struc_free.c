/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_struc_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccoto <ccoto@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 13:58:44 by ccoto         #+#    #+#                 */
/*   Updated: 2022/02/05 12:34:07 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_main	*init_main(int ac, char **av)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
	{
		printf("main : error malloc");
		return (NULL);
	}
	main->nb_philo = ft_atoi(av[1]);
	main->time_to_die = ft_atoi(av[2]);
	main->time_to_eat = ft_atoi(av[3]);
	main->time_to_sleep = ft_atoi(av[4]);
	main->time_to_die += 4;		// IS THIS CHEATING ???
	main->meals = 0;
	if (ac == 6)
		main->nb_time_to_eat = ft_atoi(av[5]);
	else
		main->nb_time_to_eat = -1;
	return (main);
}



void	init_philo(t_philo *philo, t_main *main, int *i)
{
	philo[*i].pos = *i + 1;	// CONSEC. POSITION OF PHILO
	philo[*i].main = main;
	philo[*i].nb_meals = 0;
	philo[*i].start_ttd = main->start_time;
}



void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->main->mutex_write);
	while (i < philo->main->nb_philo)
	{
		pthread_mutex_unlock(&philo->main->mutex_fork[i]); // WHY IS THIS HERE?
		pthread_mutex_destroy(&philo->main->mutex_fork[i]);
		pthread_mutex_destroy(&philo[i].timemutex);
		i++;
	}
	free(philo->main->mutex_fork);
	free(philo->main);
	free(philo);
}
