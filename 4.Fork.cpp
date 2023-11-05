#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>  
void quicksort(int [10],int,int);
int main()
{
    int pid, ppid, a[10], size, i;
    printf("\nPARENT: My process-id is %d.", getpid());
    printf("\n\nEnter the number of elements in the array: ");
    scanf("%d", &size);
    printf("Enter %d elements: ", size);
    for(i=0;i<size;i++)
    scanf("%d",&a[i]);
    printf("\nForking now!\n");
    pid = fork(); 

    if(pid==0)
    {
        printf("\nCHILD: My process-id is %d.", getpid());
        printf("\nCHILD: My parent's process-id is %d.", getppid());
        quicksort(a, 0, size-1);
        printf("\nSorted elements: ");
        for(i=0;i<size;i++)
       printf(" %d",a[i]);//printf("\nCHILD: I am dying now");
       
/*ORPHAN//
printf("\nCHILD: I am sleeping now.");
sleep(10);
printf("\n-------------------------------------------------------\n\n");
system("ps -elf | grep a.out");
*/
//ZOMBIE
        printf("\nCHILD: I am dying now");
        printf("\n-------------------------------------------------------\n\n");
        system("ps -elf | grep a.out");
        exit(0);
}
else if (pid>0)
{
        system("wait");
        printf("\nPARENT: I am back. ");
        printf("\nPARENT: My process-id is %d.", getpid());
        printf("\nPARENT: My child's process-id is %d.", pid);
        quicksort(a, 0, size-1);
        printf("\nSorted elements: ");
        for(i=0;i<size;i++)
        printf(" %d",a[i]);
        printf("\nPARENT: I am dying now.");
        printf("\n-------------------------------------------------------");
/* //ORPHAN
system("ps -elf | grep a.out");
exit(0);*/

 //ZOMBIE
        printf("\nPARENT: I am sleeping now.");
        sleep(10);
        printf("\n-------------------------------------------------------\n");
        system("ps -elf | grep a.out");
}
}
void quicksort(int a[10],int first,int last)
{
    int pivot,j,temp,i;
    if(first<last)
{
pivot=first;
        i=first;
        j=last;
        while(i<j){            while(a[i]<=a[pivot]&&i<last)
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j){
temp=a[i];
                a[i]=a[j];
                a[j]=temp;
             }
         }
         temp=a[pivot];
         a[pivot]=a[j];
         a[j]=temp;
         quicksort(a,first,j-1);
         quicksort(a,j+1,last);
    }
}

