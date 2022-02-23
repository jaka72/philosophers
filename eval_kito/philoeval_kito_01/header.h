/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:14:42 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/02/23 13:15:15 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_data
{
	int					nrfilos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals_per_philo;
	int					count_meals;
	long long			startofsession;
	pthread_mutex_t		mutex_time; // is this one necessary
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_death;
	pthread_mutex_t		*mutex_forks;
	pthread_t			thread_timer;
	int					hasdied;
	int					mealsreached;
}	t_data;

typedef struct s_philosopher
{
	t_data				*d;
	int					id;
	unsigned long long	new_start_time;
	long long			deadline;
	pthread_t			thread;
}	t_philo;

int			check_and_store_arguments(int argc, char **argv, t_data *d);
int			ft_isdigit(int c);
void		message(t_philo *ph, char *str, unsigned long long time);
int			msg_and_free(t_philo *ph, t_data *d, char *str, int ret);
int			print_and_return(int code, char *msg);
void		free_all(t_philo *ph, t_data *d);
void		join_threads(t_data data, t_philo *philo_struct);
void		*start_philo(void *philo);
int			timer(t_philo *ph);
void		mysleep(int milisecs);
long long	get_time(void);
int			ft_atoi(const char *str);

#endif
