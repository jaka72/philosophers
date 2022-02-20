#include "newheader.h"

void	mysleep(int milisecs)
{
	long int	a;
	long int	b;
	long int	deadline;
	struct		timeval t;

	gettimeofday(&t, NULL);
	a = t.tv_sec * 1000000 + t.tv_usec;
	deadline = a + milisecs * 1000;
	b = 0;
	while (b <= deadline)
	{
		usleep(10);
		gettimeofday(&t, NULL);
		b = t.tv_sec * 1000000 + t.tv_usec;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
