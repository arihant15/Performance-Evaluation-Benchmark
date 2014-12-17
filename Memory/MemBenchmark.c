#include <stdio.h> 
#include <sys/time.h>
#include <string.h>
#include <memory.h>
#include <pthread.h>


char str1[9999999];
long n = 5242880, lc, buffer_size;
struct timeval t;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

long timediff(clock_t t1, clock_t t2) 
{
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000000 ;
    return elapsed;
}
double genavg(double a[])
{
    int s;
    double sum=0;
    double avg;
 for(s = 0; s < 10000; s++)
    {
        sum+=a[s];
    }
    avg= sum/10000;
    return avg;

}

void mkdata(long n)
{
	printf("Constructing the file...\n");
    int i;
    for (i = 0; i < n; ++i)
    {
        str1[i]= (char)((rand()% 10)+97);
       
    }
}

void *seqread()
{
    char temp[n];
    long m;
    pthread_mutex_lock( &mutex1 );

    for(m = 0; m < lc; m += buffer_size)
        memcpy(temp, str1, buffer_size);

    pthread_mutex_unlock( &mutex1 );
}

void *seqwrite()
{
    char str3[n];
    long q;
    pthread_mutex_lock( &mutex1 );

	for(q = 0; q < lc; q += buffer_size)
		strncpy(str3, str1, buffer_size);

	pthread_mutex_unlock( &mutex1 );
}

void *randread()
{
	long w, v;
	char temp[n];
	pthread_mutex_lock( &mutex1 );

    for (w = 0; w < lc; w += buffer_size) 
    {
        v = rand()% 200;
        memcpy(&temp[v], &str1[v], buffer_size);
    }
    pthread_mutex_unlock( &mutex1 );
}

void *randwrite()
{
    long e, g;
    char str3[n];
    pthread_mutex_lock( &mutex1 );

    for (e = 0;e < lc; e += buffer_size)
    { 
        g = rand()% 200;
        strncpy(&str3[g], &str1[g], buffer_size);
    }
    pthread_mutex_unlock( &mutex1 );
}
// Latency Calculation

void latency(long buffer_size1, long buffer_size)
{
    long r;
    char str5[n];
    clock_t t1,t2;
    double elapsed[10000];
    double tt;
    
    for(r=0; r<10000; r+=1) 
    {
        t1= clock();

        memcpy(&str5[r], &str1[r] , buffer_size); 
        
        t2= clock();
        
        elapsed[r] = timediff(t1, t2);

    }
    tt= genavg(elapsed);
    printf("Latency: %lf ns\n", tt);
}
/* Was used to compute the avg of values
void perfavg(float ca1[],float ca2[],float ca3[],float ca4[])
{
    int y;
    float av1=0,av2=0,av3=0,av4=0;
    for(y=0; y<30; y++)
    {
        av1+=ca1[y];
        av2+=ca2[y];
        av3+=ca3[y];
        av4+=ca4[y];
    }
    printf("\nThe average throguhput for seq read is :%f\n",av1/30);
    printf("The average throguhput for seq write is :%f\n",av2/30);
    printf("The average throguhput for rand read is :%f\n",av3/30);
    printf("The average throguhput for rand write is :%f\n",av4/30);

}*/
int main()
{
	int threadct, i, j, k, l, p, o, u, y,q;
	double s_t, e_t, t_t, tt;
    float ca1[40], ca2[40], ca3[40], ca4[40];


	//printf("Enter the size of the array :");
	//scanf("%ld",&n);
    printf("Enter the number of threads you want to create:");
    scanf("%d",&threadct);
    //threadct=1;
    pthread_t threads[threadct];
	printf("\nEnter the size(1 byte/1024 bytes/1048576 bytes:");
    scanf("%ld",&buffer_size);
    //buffer_size=1;
    mkdata(n);
   	lc = n/threadct;
   	//Seq Read
   	gettimeofday(&t, NULL);
	s_t = t.tv_sec+(t.tv_usec/1000000.0);
    for( i=0;i<threadct;i++)
    {
        //printf("\nCreating Thread: %d \n\n", (i+1));
        pthread_create(&threads[i],NULL, &seqread, NULL);
    } 
    for(p =0; p < threadct; p++)
	{
		pthread_join(threads[p], NULL);
	}
    gettimeofday(&t, NULL);
	e_t = t.tv_sec+(t.tv_usec/1000000.0);
	t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    //tput3=((n/1048576)/elapsed11);
    //ca1[q]=(n/t_t)/(1024*1024);
    printf("Throughput for seq read = %lf \n", (n/t_t)/(1024*1024));
    sleep(1);

    // Seq Write
	gettimeofday(&t, NULL);
	s_t = t.tv_sec+(t.tv_usec/1000000.0);    
    for(j = 0; j < threadct; j++)
    {
        //printf("\nCreating Thread: %d \n\n", (j+1));
        pthread_create(&threads[j],NULL, &seqwrite, NULL);
    }
    for(o =0; o < threadct; o++)
	{
		pthread_join(threads[o], NULL);
	}
    gettimeofday(&t, NULL);
	e_t = t.tv_sec+(t.tv_usec/1000000.0);
	t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    ca2[q]=(n/t_t)/(1024*1024);
    printf("Throughput for seq write = %lf \n",(n/t_t)/(1024*1024));
    sleep(1);


    // Rand Read 
    gettimeofday(&t, NULL);
	s_t = t.tv_sec+(t.tv_usec/1000000.0);
    for(k = 0; k < threadct; k++)
    {
        //printf("\nCreating Thread: %d \n\n", (k+1));
        pthread_create(&threads[k],NULL, &randread, NULL);
    }
    for(u =0; u < threadct; u++)
	{
		pthread_join(threads[u], NULL);
	}
    gettimeofday(&t, NULL);
	e_t = t.tv_sec+(t.tv_usec/1000000.0);
	t_t = e_t - s_t;
    printf("Time elapsed using threads: %lf Sec\n", t_t);
    ca3[q]=(n/t_t)/(1024*1024);
    printf("Throughput for rand read = %lf \n", (n/t_t)/(1024*1024));
    sleep(1);

    // Rand Write
    gettimeofday(&t, NULL);
	s_t = t.tv_sec+(t.tv_usec/1000000.0);

    for(l = 0; l < threadct; l++)
    {
        //printf("\nCreating Thread: %d \n\n", (l+1));
        pthread_create(&threads[l],NULL, &randwrite, NULL);
    }
    for(y =0; y < threadct; y++)
	{
		pthread_join(threads[y], NULL);
	}
    gettimeofday(&t, NULL);
	e_t = t.tv_sec+(t.tv_usec/1000000.0);
	t_t = e_t - s_t;

    printf("Time elapsed using threads: %lf Sec\n", t_t);
    ca4[q]=(n/t_t)/(1024*1024);
    printf("Throughput for rand write =%lf \n",(n/t_t)/(1024*1024));
    sleep(1);


    printf("Ending...\n");
// Latency function call

    latency(buffer_size,buffer_size);
    //compute avg
    //perfavg(ca1,ca2,ca3,ca4);
    

	return 0;	
}