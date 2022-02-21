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

long long	get_time(t_philo *ph)
{
	struct timeval	t;
	long long		time;

	ph->d = ph->d;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void	message(t_philo *ph, char *str, unsigned long long time)
{
	unsigned long long	mspassed;

	mspassed = time - ph->d->startofsession;
	pthread_mutex_lock(&ph->d->mutex_death);
	if (ph->d->hasdied == 0 && ph->d->mealsreached == 0)
		printf("%lld %d %s\n", mspassed, ph->id + 1, str);
	pthread_mutex_unlock(&ph->d->mutex_death);
}

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

// static int	overflow(int sign, long long num, const char *str, int i)
// {
// 	if (sign == -1 && str[i] > '8')
// 		return (0);
// 	if (sign == -1 && num > 922337203685477580)
// 		return (0);
// 	if (sign == 1 && str[i] > '7')
// 		return (-1);
// 	if (sign == 1 && num > 922337203685477580)
// 		return (-1);
// 	else
// 	{
// 		num = (num * 10) + (str[i] - '0');
// 		return (num * sign);
// 	}
// }

// int			ft_atoi(const char *str)
// {
// 	int			i;
// 	int			sign;
// 	long long	num;

// 	i = 0;
// 	sign = 1;
// 	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	num = 0;
// 	while (str[i] && ft_isdigit(str[i]))
// 	{
// 		if (num >= 922337203685477580)
// 			return (overflow(sign, num, str, i));
// 		num = num * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (num * sign);
// }
