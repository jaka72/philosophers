/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 17:29:01 by jmurovec      #+#    #+#                 */
/*   Updated: 2022/03/07 18:04:33 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_args_digits(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (print_and_return(1, "Error nr arguments\n"));
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (print_and_return(1,
						"Error: arguments not only digits\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_meals(int argc, char **argv, t_data *d)
{
	if (argc == 6)
	{
		d->max_meals_per_philo = ft_atoi(argv[5]);
		if (d->max_meals_per_philo == 0)
			return (1);
		else if (d->max_meals_per_philo < 0)
			return (print_and_return(1, "Error: Invalid argument\n"));
	}
	return (0);
}

void	check_args_and_init(char **argv, t_data *d)
{
	d->nrfilos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	d->time_to_wait = d->time_to_eat * 0.1;
	d->max_meals_per_philo = -1;
	d->count_meals = 0;
	d->hasdied = 0;
	d->mealsreached = 0;
}

int	store_arguments(int argc, char **argv, t_data *d)
{
	check_args_and_init(argv, d);
	if (d->nrfilos <= 0 || d->time_to_die < 1 || d->time_to_eat < 0
		|| d->time_to_sleep < 0)
		return (print_and_return(1, "Error: Invalid argument value\n"));
	if (check_meals(argc, argv, d) != 0)
		return (1);
	return (0);
}

int	check_and_store_arguments(int argc, char **argv, t_data *d)
{
	if (check_args_digits(argc, argv) == 1)
		return (1);
	if (store_arguments(argc, argv, d) != 0)
		return (1);
	return (0);
}
