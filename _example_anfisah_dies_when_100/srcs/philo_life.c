/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccoto <ccoto@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 10:57:48 by ccoto         #+#    #+#                 */
/*   Updated: 2022/02/08 10:33:52 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_msg(t_philo *philo, char *msg)
{
	// IS IT NECESSARY TO LOCK PRINTING? APPARENTLY IT PREVENTS WRONG TIME ORDERS
	pthread_mutex_lock(&philo->main->mutex_write);
	//printf("%lldms %d %s", timestamp(philo), philo->pos, msg);
	  printf("%lld %d %s", timestamp(philo), philo->pos, msg);
	pthread_mutex_unlock(&philo->main->mutex_write);
}




void	number_meals(t_philo *philo)
{
	//pthread_mutex_lock(&philo->main->mutex_fork[philo->pos - 1]);
	//print_msg(philo, "has taken a fork\n");
	//pthread_mutex_lock(&philo->main->mutex_fork[((philo->pos % philo->main->nb_philo))]);
	
	
	
	//print_msg(philo, "has taken a fork\n");
	//print_msg(philo, "has taken a fork\n"); // DOES THIS ORDER MATTER ???
	philo->nb_meals++;
	if (philo->nb_meals == philo->main->nb_time_to_eat)
		philo->main->meals++; // HERE PROBABLY COUNTING, WHEN TO STOP AND EXIT
}




void	*philo_life(void *arg)
{
	t_philo			*philo;
	struct timeval	newstart;

	philo = arg;
	if (philo->pos % 2 == 0)	// EVERY ODD, THEN EVERY EVEN
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->main->mutex_fork[philo->pos - 1]);
		pthread_mutex_lock(&philo->main->mutex_fork[((philo->pos % philo->main->nb_philo))]);

//		number_meals(philo);					// HERE IT FIRST LOCKS BOTH, THEN PRINTS "taken fork 2x" 
		
		print_msg(philo, "is eating\n");		// IT LOCKS WHEN PRINTING MSG, WITH MUTEX-WRITE

//		printf("%lld %d is eating\n", timestamp(philo), philo->pos);
//		IT OCCASIONALLY PRINTS IN WRONG TIME ORDER

		
		pthread_mutex_lock(&philo->timemutex);	// WHY IS TIME-MUTEX SEPARATE? THIS IS ALREADY INSIDE
		gettimeofday(&newstart, NULL);			// 							OF LOCKED FORK-MUTEX
		pthread_mutex_unlock(&philo->timemutex);
		
		philo->start_ttd = newstart.tv_sec * 1000 + newstart.tv_usec / 1000;
		//printf("... start_ttd %lld\n", philo->start_ttd);
		usleep(philo->main->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->main->mutex_fork[philo->pos - 1]);
		pthread_mutex_unlock(&philo->main->mutex_fork[((philo->pos % philo->main->nb_philo))]);
		
		//print_msg(philo, "is sleeping\n");
		usleep(philo->main->time_to_sleep * 1000);
		//print_msg(philo, "is thinking\n");
	}
}




int	is_dead(t_philo *philo, unsigned long long *curr_time)
{
	if (*curr_time > philo->main->time_to_die)
	{
		pthread_mutex_lock(&philo->main->mutex_write);
		printf("%lldms %d %s", timestamp(philo), philo->pos, "died");
		pthread_mutex_destroy(&philo->main->mutex_write);
		return (1);
	}
	if (philo->main->meals == philo->main->nb_philo)
	{
		pthread_mutex_lock(&philo->main->mutex_write);
		printf("Meals per philosopher: %d\n", philo->main->nb_time_to_eat);
		return (1);
	}
	return (0);
}



int	live_or_dead(t_main *main, t_philo *philo)
{
	int					i;
	struct timeval		time;
	unsigned long long	curr_time;

	while (1)
	{
		i = 0;
		usleep(2000);
		while (i < main->nb_philo)
		{
			pthread_mutex_lock(&philo[i].timemutex);
			gettimeofday(&time, NULL);
			curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
			curr_time = curr_time - philo[i].start_ttd;
			
			//if (is_dead(philo, &curr_time) == 1)
			//	return (1);

			if (curr_time > philo->main->time_to_die)
			{
				//pthread_mutex_lock(&philo->main->mutex_write);
				printf("%lldms %d %s", timestamp(philo), philo->pos, "died");
				//pthread_mutex_destroy(&philo->main->mutex_write);
				return (1);
			}



			pthread_mutex_unlock(&philo[i].timemutex);
			i++;
		}
	}
	return (0);
}
