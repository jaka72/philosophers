/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoto <ccoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:57:31 by ccoto             #+#    #+#             */
/*   Updated: 2021/08/19 13:55:48 by ccoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
	int					nb_philo;
	unsigned long long	time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_time_to_eat;
	int					meals;
	struct timeval		start;
	unsigned long long	start_time;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_write;
}				t_main;

typedef struct s_philo
{
	t_main				*main;
	int					pos;
	int					nb_meals;
	struct timeval		time;
	unsigned long long	time_in_mill;
	unsigned long long	start_ttd;
	pthread_mutex_t		timemutex;
	pthread_t			thread;
}				t_philo;

t_main		*init_main(int ac, char **av);
int			condition(int count, int sign, int nb);
int			ft_atoi(const char *str);
long long	timestamp(t_philo *philo);
void		*philo_life(void *arg);
int			init_mutex(t_main *main, t_philo *philo);
int			create_threads(t_main *main, t_philo *philo);
int			ft_isdigit(int c);
int			parse_arg(char **av, t_main *main);
int			live_or_dead(t_main *main, t_philo *philo);
void		print_msg(t_philo *philo, char *msg);
int			is_dead(t_philo *philo, unsigned long long *curr_time);
void		ft_free(t_philo *philo);
void		init_philo(t_philo *philo, t_main *main, int *i);
int			philosophers(t_main *main, t_philo *philo);
void		number_meals(t_philo *philo);

#endif