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




int	main(void)
{
	pthread_t	th;

	char	*text;
	text = NULL;
	free(text);



	text = NULL;
	printf("before malloc [%s]\n", text);
	text = malloc(sizeof(char)* 5);
	printf("after malloc [%s]\n", text);
	text = NULL;
	printf("after malloc [%s]\n", text);




	int			x;
	pthread_t	thread[1];

	pthread_create(&thread[0], NULL, &myfunc, (void*)&x);
	//pthread_join(thread[0], NULL);
	//pthread_detach(thread[0]);	// STILL RECHABLE 11 bytes, IF MAIN ENDS BEFORE myfunc

	//sleep(2);

	printf("At end\n");
	free(text);


	char *list_errors[5] =
	{
		"Error initializing a mutex",
		"Error creating a thread",
	};

	printf("first message %s\n, second %s\n", list_errors[0], list_errors[6]);



	return (0);
}