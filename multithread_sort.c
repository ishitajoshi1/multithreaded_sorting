#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
/*Write a multithreaded sorting program in c that works as follows: A list of integers is divided into two smaller lists of equal size. 
Two separate threads (which we will term sorting threads) sort each sublist using a sorting algorithm of your choice. 
The two sublists are then merged by a third thread - a merging thread - which merges the two sublists into a single sorted list.*/
void divarr(int arr[]);
void bubble_sort(int arr[],int n);
void mergeArrays(int arr1[], int arr2[],int n1,int n2,int arr3[]);
int arr[20],n,a1[10],a2[10];//array 'arr' to be divided into arrays 'a1' and 'a2','n' represents the size of 'arr' entered by user
sem_t mutex;//binary semaphore for synchronization
int i,j;//global variables for traversing through arrays
void *thread1(void *arg)//sorting thread 1
{ 
  sem_wait(&mutex);//no other thread can run
  bubble_sort(a1,(n-n/2));

        sleep(1);
  sem_post(&mutex);//other thread can run
}
void *thread2(void *arg)//sorting thread 2
{
  sem_wait(&mutex);
  bubble_sort(a2,n/2);
  sleep(1);
  sem_post(&mutex);
}
void *thread3(void *arg)//merging thread 3
{ 
  sem_wait(&mutex);
mergeArrays(a1,a2,n/2,n-n/2,arr);
printf("Merged Array\n");
	for(i=0;i<n;i++)
	printf("%d\n",arr[i]);
sleep(1);
sem_post(&mutex);
}
int main()//main program
{  
    printf("Enter size of array\n");
    scanf("%d",&n);
 if(n%2!=0)//will accept only even values as asked in question to divide array in two equal parts
{ 
  printf("Incorrect entry\n");
  exit(0);
}
printf("Enter %d elements\n",n);
    for(i=0;i<n;i++)//storing elements
    scanf("%d",&arr[i]);
   
    divarr(arr);
sem_init(&mutex,0,1);
pthread_t t1,t2,t3;
pthread_create(&t1,NULL,thread1,NULL);//create thread_1	
pthread_join(t1,NULL);
pthread_create(&t2,NULL,thread2,NULL);//create thread_2
pthread_join(t2,NULL);
pthread_create(&t3,NULL,thread3,NULL);//create thread_3
pthread_join(t3,NULL);
}
void divarr(int array[])//divide array in 2 sub arrays a1 and a2
{        
        int mpt=n/2,rem=n-n/2;//mpt is midpoint and rem is remaining list size
	for(i=0,j;i<mpt;i++,j++)
	a1[j]=arr[i];
	for(i=mpt,j=0;i<n,j<rem;i++,j++)
	a2[j] = arr[i];
	printf("Subarray1\n");
	for(i=0;i<mpt;i++)
	printf("%d\n",a1[i]);
	printf("Subarray2\n");
	for(i=0;i<rem;i++)
	printf("%d\n",a2[i]);
        
}
void bubble_sort(int a[], int n)//using bubble sort to sort the sub arrays 
{  
   int tmp;
   for (i = 0; i < n; i++) 
   {   // loop n times - 1 per element
       for (j = 0; j < n - i - 1; j++) 
	   { // last i elements are sorted already            
            if (a[j] > a[j + 1]) 
	    { // swap if order is broken
              tmp = a[j];
              a[j] = a[j + 1];
              a[j + 1] = tmp;
           }
       }
   }
   printf("Sorted subarray\n");
        for(i=0;i<n;i++)
	printf("%d\n",a[i]);
}
void mergeArrays(int arr1[], int arr2[],int n1,int n2,int arr3[]) //merging the sorted arrays through merge sort
{   
    int a=0,b=0,k = 0;   
    // Traverse both array 
    while (a<n1 && b <n2) 
    { 
        if (arr1[a] < arr2[b]) 
            arr3[k++] = arr1[a++]; 
        else
            arr3[k++] = arr2[b++]; 
    }
    // Store remaining elements of first array 
    while (a< n1) 
        arr3[k++] = arr1[a++]; 
    // Store remaining elements of second array 
    while (b < n2) 
        arr3[k++] = arr2[b++]; 
}

