#include<sys/shm.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#define SIZE 400
#define data_not_filled -1
#define data_filled 0
#define data_read_client 1
typedef struct data
{
	int status;
	char buff[100];
}data1;

int main()
{
	int key=0,shmid,i=0;
	key=ftok(".",'A');
	char ch;
	data1 *shm_ptr;
	shmid=shmget(key,SIZE,IPC_CREAT|0666);

	shm_ptr=(data1*)shmat(shmid,NULL,0);
	printf("%s",shm_ptr->buff);
	while(shm_ptr->status!=data_read_client)
	{
		printf("\nClient is reading the data ");
		sleep(1);
		break;
	}
	shmdt(shm_ptr);
	shmctl(shmid,IPC_RMID,0);
	printf("\nTerminated\n");
	return 0;
}

