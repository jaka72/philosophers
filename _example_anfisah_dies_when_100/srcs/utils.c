/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccoto <ccoto@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 10:57:56 by ccoto         #+#    #+#                 */
/*   Updated: 2022/02/07 16:33:40 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	condition(int count, int sign, int nb)
{
	if (count > 20 && sign < 0)
		return (0);
	else if (count > 20 && sign > 0)
		return (-1);
	else
		return (sign * nb);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;
	int	count;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	count = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		count++;
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	return (condition(count, sign, nb));
}

long long	timestamp(t_philo *philo)
{
	struct timeval		time;
	long long	timeinmill;
	
	gettimeofday(&time, NULL);
	timeinmill = time.tv_sec * 1000
		+ time.tv_usec / 1000;
	timeinmill = timeinmill - philo->main->start_time;
	
	//printf("timestamp    %lld\n", philo->main->start_time);
	//printf("time in mill %lld\n", philo->time_in_mill);
	return (timeinmill);
}


// MINE SEEMS TO WORK JUST FINE
// long long	timestamp(t_philo *ph)
// {
// 	unsigned long 		timestamp;
// 	unsigned long long	newtime; // maybe it is enough just long int ???
// 	struct timeval		t;
// 	gettimeofday(&t, NULL);
// 	newtime = t.tv_sec * 1000 + t.tv_usec / 1000;
// 	timestamp = newtime - ph->main->start_time;
// 	return (timestamp);
// }


int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
