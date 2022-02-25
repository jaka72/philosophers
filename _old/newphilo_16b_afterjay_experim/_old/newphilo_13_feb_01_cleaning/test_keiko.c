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

void show_long(long int li)
{
	printf("show long %ld\n", li);

}


#include <limits.h>
#include <float.h>


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
	

	// int i = 0;
	// while (i < 100)
	// {
	// 	printf("a ");
	// 	i++;
	// }



    printf("CHAR_BIT    :   %d\n", CHAR_BIT);
    printf("CHAR_MAX    :   %d\n", CHAR_MAX);
    printf("CHAR_MIN    :   %d\n", CHAR_MIN);
    printf("INT_MAX     :   %d\n", INT_MAX);
    printf("INT_MIN     :   %d\n", INT_MIN);
    printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
    printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
    printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
    printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
    printf("SHRT_MAX    :   %d\n", SHRT_MAX);
    printf("SHRT_MIN    :   %d\n", SHRT_MIN);
    printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
    printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
    printf("ULONG_MAX   :   %lu\n", 			 ULONG_MAX);
    printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);



	int i;
	float f;
	double d;
	long unsigned li = 18446744073709551615U;  // my comp not possible
//		long int li =   9223372036854775807;
//		INT_MAX     :    		 2147483647
//				sec              1644504821
//				mic                  572666
//				time       1644504821572666   micro
//				tim        1644504947911   mili
//						   1644505044654
	struct timeval t;
	long int time;
	gettimeofday(&t, NULL);
	printf("sec %ld\n", t.tv_sec);
	printf("mic %ld\n", t.tv_usec);

	time = t.tv_sec * 1000000 + t.tv_usec;
	time = time / 1000;

	printf("time %ld\n", time);

//	show_long(li);

	return (0);
}