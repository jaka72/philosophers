#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// #include <time.h>
// #include <sys/time.h>

void *myfunc(void *i)
{
    int *x;

    x = (int*)i;
    *x = 33;
	sleep(2);
	printf("\nPrint from myfunc()\n");
    return (0);
}


int main(void)
{
	int			i;
	pthread_t	mythread01;

	i = 0;
	pthread_create(&mythread01, NULL, myfunc, (void*)&i);

	//pthread_detach(mythread01);   // DETACH - THE MAIN CONTINUES WITHOUT WAITING
                                    // FOR myfunc TO RETURN

	pthread_join(mythread01, NULL); // JOIN - WAITS FOR myfunc TO RETURN

	sleep(1);
	printf("In main, after join or detach. i = %d\n", i);



  return 0;
}