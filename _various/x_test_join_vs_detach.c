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

// With mallocing:
//    IF myfunc RETURNS WITHOUT free(): 					IT'S DEFINITELY LOST 11 bytes
//    IF MAIN ENDS BEFORE myfunc FREES: 					IT'S STILL REACHABLE 11 bytes
// No mallocing:
//    IF DETACH IS CALLED AND myfunc SLEEPS AND MAIN ENDS: IT'S POSSIBLY LOST 272 bytes

void *myfunc(void *x)
{
	char *str = malloc(sizeof(char) * 11);
	//sleep(1);
	free(str); // STILL REACHABLE 11 bytes, WHEN MAIN ENDS BEFORE myfunc
	return (0);
}

typedef struct s_philo
{
	int				x;
	pthread_t		thr[1];
	//pthread_t		*thr;
	pthread_mutex_t	mut1;
} t_philo;


void *mysleep(void *philo)
{
	t_philo *ph;

	ph = philo;
	//sleep(2);
	// while (1)
	pthread_mutex_lock(&ph->mut1);
	printf(" ...... \n");
	sleep(1);
	pthread_mutex_unlock(&ph->mut1);
	return 0;
}



int	main(void)
{
	// int			x;
	// pthread_t	thread[1];
	// pthread_t	*th;
	// pthread_mutex_t	mut1;
	// char	*text;

	// text = NULL;
	// free(text);

	// text = NULL;
	// printf("before malloc [%s]\n", text);
	// text = malloc(sizeof(char)* 5);
	// printf("after malloc [%s]\n", text);
	// text = NULL;
	// printf("after malloc [%s]\n", text);

	t_philo *ph;

	ph = malloc(sizeof(t_philo));

	pthread_mutex_init(&ph[0].mut1, NULL);

//	pthread_create(&thread[0], NULL, &myfunc, (void*)&x);
	pthread_create(&ph->thr[0], NULL, &mysleep, (void*)&ph[0]);
	//pthread_detach(thread[0]);	// STILL RECHABLE 11 bytes, IF MAIN ENDS BEFORE myfunc

	//usleep(5000);

	//pthread_mutex_unlock(&ph->mut1);

	pthread_join(ph->thr[0], NULL);
//	pthread_detach(ph->thr[0]);

//	pthread_mutex_destroy(&ph[0].mut1);

	printf("After sleep\n");
	
	
	//free(text);


	// char *list_errors[5] =
	// {
	// 	"Error initializing a mutex",
	// 	"Error creating a thread",
	// };

	// printf("first message %s\n, second %s\n", list_errors[0], list_errors[6]);

	free(ph);

	return (0);
}