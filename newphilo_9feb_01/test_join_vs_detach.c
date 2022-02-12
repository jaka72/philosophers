#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <float.h>

void	*test(void *arg)
{
	char	*s;
	//usleep(500);

	s = (char *)arg;
	s[0] = '1';
	s[1] = '2';	
	usleep(500);
	return (s);
}


void *myfunc(void *x)
{
	usleep(10000000);
	return (0);
}



int	main(void)
{
	pthread_t	th;
	char	*text;

	text = malloc(sizeof(char)* 5);

	

	struct timeval t;
	long int time;
	gettimeofday(&t, NULL);
	printf("sec %ld\n", t.tv_sec); printf("mic %ld\n", t.tv_usec);
	time = t.tv_sec * 1000000 + t.tv_usec;
	time = time / 1000;
	printf("time %ld\n", time);


	int			x;
	pthread_t	thread[1];

	pthread_create(&thread[0], NULL, &myfunc, (void*)&x);
	//pthread_join(thread[0], NULL);
	pthread_detach(thread[0]);


	printf("At end\n");

	free(text);
	return (0);
}