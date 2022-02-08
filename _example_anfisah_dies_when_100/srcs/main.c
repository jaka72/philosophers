/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccoto <ccoto@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 10:57:39 by ccoto         #+#    #+#                 */
/*   Updated: 2022/02/08 08:32:25 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parse_arg(char **av, t_main *main)
{
	int	i;
	int	j;

	if (main->nb_philo < 1 || main->time_to_die < 60 || main->time_to_eat < 60
		|| main->time_to_sleep < 60 || main->nb_philo > 200)
	{
		printf("Error arguments: 1 philosopher minimum\n");
		return (1);
	}
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("Error arguments: not only digit\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


int	init_mutex(t_main *main, t_philo *philo)
{
	int	i;

	if (pthread_mutex_init(&main->mutex_write, NULL) != 0		// WHAT ARE THESE MUTEXES ????
		|| pthread_mutex_init(&philo->timemutex, NULL) != 0)
	{
		printf("Impossible to init mutex");
		return (1);
	}
	main->mutex_fork = malloc(sizeof(pthread_mutex_t) * main->nb_philo);
	if (!main->mutex_fork)
	{
		printf("mutex_fork : error malloc");
		return (1);
	}
	
	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_mutex_init(&main->mutex_fork[i], NULL) != 0) // THE SAME
		{
			printf("Impossible to init mutex");
			return (1);
		}
		i++;
	}
	return (0);
}




// int	create_threads(t_main *main, t_philo *philo)
// {
// 	int	i;
// 	int	error;

// 	i = 0;
// 	gettimeofday(&main->start, NULL);
// 	main->start_time = main->start.tv_sec * 1000 + main->start.tv_usec / 1000;
// 	while (i < main->nb_philo)
// 	{
// 		init_philo(philo, main, &i);
// 		error = pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]);
// 		if (error != 0)
// 		{
// 			printf("Thread can't be created\n");
// 			return (1);
// 		}
// 		error = pthread_detach(philo[i].thread);	// WHAT IS THIS
// 		if (error != 0)
// 		{
// 			printf("Impossible to detach threads\n");
// 			return (1);
// 		}
// 		error = pthread_join(philo[i].thread, NULL); // JOINING IN THE SAME LOOP ???
// 		// here no error check needed ???
// 		i++;
// 	}
// 	return (0);
// }




int	create_threads(t_main *main, t_philo *philo)
{
	int	i;
	int	error;
	struct timeval time;

	i = 0;
	gettimeofday(&time, NULL);
	main->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < main->nb_philo)
	{
		init_philo(philo, main, &i);
		error = pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]);
		if (error != 0)
		{
			printf("Thread can't be created\n");
			return (1);
		}
		error = pthread_detach(philo[i].thread);
		if (error != 0)
		{
			printf("Impossible to detach threads\n");
			return (1);
		}
		error = pthread_join(philo[i].thread, NULL); // WHY JOIN, AFTER DETACH ???
		// here no error check needed ???
		i++;
	}
	return (0);
}



int	philosophers(t_main *main, t_philo *philo)
{
	if (!philo)
	{
		printf("philo : error malloc");
		return (1);
	}
	if (init_mutex(main, philo) == 1)	// MALLOCING FORK-MUTEXES + loop(pthread_mutex_init)
	{									// and also 2x pthread_mutex_init()  mutex-write and timemutex
		ft_free(philo);
		return (1);
	}
	if (create_threads(main, philo) == 1)
	{
		ft_free(philo);
		return (1);
	}
	if (live_or_dead(main, philo) == 1)
	{
		ft_free(philo);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main	*main;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Error arguments: bad number of arguments\n");
		return (1);
	}
	//main = NULL;
	// IF YOU WANT TO PASS A STRUCT AS AN ARGUMENT, IT NEEDS TO BE MALLOCED BEFOREHAND
	// IT CANNOT BE MALLOCED INSIDE THE FUNCTION, INTO WHICH IT WAS PASSED !
	main = init_main(ac, av);
	//init_main(ac, av, main);

	printf(" is it saved? time to eat %d\n", main->time_to_eat);

	if (main == NULL)
		return (1);
	if (parse_arg(av, main) == 1)
		return (1);
	philo = malloc(sizeof(t_philo) * main->nb_philo);
		// No error check ???

	if (philosophers(main, philo) == 1)
		return (1);
	return (0);
}
