#include<stdio.h>
#include<pthread.h>

void* reader(void*);
void* writer(void*);
int writebuff();
void readbuff(int buffer);	
pthread_mutex_t lock;
int flag=0; 
int buff;

int main()
{
       
	pthread_t rid;
	pthread_t wid;
	pthread_create(&wid,NULL,writer,NULL);
	pthread_create(&rid,NULL,reader,NULL);
	pthread_join(wid,NULL);
	pthread_join(rid,NULL);
return 0;
}
void* reader(void *para)
{
	while(1)
	{
		pthread_mutex_lock(&lock); //mutex lock acquire
		if(flag==1)   //flag =1 means buffer is full
		{		
			readbuff(buff);
			flag=0;   //flag =0 means buffer i empty
		}
		pthread_mutex_unlock(&lock); //mutex lock release
	}
}


void* writer(void *para)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(flag == 0)
		{		
		buff = writebuff();
		flag=1;
		}
	pthread_mutex_unlock(&lock);
	}
}
			 
int writebuff()
{
	int writevalue;
	printf("\nWRITER is writing in Buffer\n");
	scanf("%d",&writevalue);
	return writevalue;
}
void readbuff(int buffer)
{
	printf("READER is reading from buffer=%d\n",buffer);
}
