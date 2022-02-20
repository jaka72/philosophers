#include "newheader.h"

// void	mysleep(int milisecs)
// {
// 	long int	a;
// 	long int	b;
// 	long int	deadline;
// 	struct		timeval t;

// 	gettimeofday(&t, NULL);
// 	a = t.tv_sec * 1000000 + t.tv_usec;
// 	deadline = a + milisecs * 1000;
// 	b = 0;
// 	while (b <= deadline)
// 	{
// 		usleep(1000);
// 		gettimeofday(&t, NULL);
// 		b = t.tv_sec * 1000000 + t.tv_usec;
// 	}
// }


void	mysleep(int milisecs, long long new_start)
{
	//long int	a;
	long int		time;
	long long int	deadline;
	struct			timeval t;

	//gettimeofday(&t, NULL);
	//deadline = (t.tv_sec * 1000 + t.tv_usec / 1000) + milisecs;
	//deadline = a + milisecs;
	deadline = new_start + milisecs;
	time = 0;
	while (time <= deadline)
	{
		usleep(50);
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000 + t.tv_usec / 1000;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
