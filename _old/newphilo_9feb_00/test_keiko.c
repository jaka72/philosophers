#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
//#include "libft/libft.h"

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

int	main(void)
{
	pthread_t	th;
	char	*text;

	text = malloc(sizeof(char)* 5);
	text[0] = 'H';
	text[1] = 'i';
	printf("now text is %s\n", text);	
	pthread_create(&th, NULL, &test, text);
	pthread_detach(th);
		//free(text);
	usleep(2000);
	printf("now text is %s\n", text);
	

	int i = 0;
	while (i < 100)
	{
		printf("a ");
		i++;
	}


	usleep(1000000);
	return (0);
}