#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<pthread.h>

long loop_count,l_c, th_count;
struct timeval t;
double f_avg, i_avg;

// Thread Structure for FLOPS
struct fth
{
	int lc, th_counter;
	float fa, fb, fc, fd;
	pthread_t threads;
};

// FlOPs Benchmark
void *FAdd(void *data)
{
	struct fth *th_d;
	th_d = (struct fth *) data;

	for(th_d->lc = 1; th_d->lc <= l_c; th_d->lc++)
	{
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
		th_d->fa + th_d->fd;
		th_d->fa + th_d->fb;
		th_d->fb + th_d->fc;
		th_d->fa - th_d->fb;
	}
}

void FLOPSBenchmark()
{
	long l, c, m, id;
	double fs_t, fe_t, ft_t;
	struct fth ft[th_count];

	for(l =0; l < th_count; l++)
	{
		ft[l].lc = 1;
		ft[l].th_counter = 1;
		ft[l].fa = 0.02;
		ft[l].fb = 0.2;
		ft[l].fc = 0;
		ft[l].fd = 0;
	}

	gettimeofday(&t, NULL);
	fs_t = t.tv_sec+(t.tv_usec/1000000.0);

	for(c = 0; c < th_count; c++)
	{
		pthread_create(&ft[c].threads, NULL, &FAdd, (void *)&ft[c]);
	}
	for(m =0; m < th_count; m++)
	{
		pthread_join(ft[m].threads, NULL);
	}

	gettimeofday(&t, NULL);
	fe_t = t.tv_sec+(t.tv_usec/1000000.0);
	ft_t = fe_t - fs_t;
	f_avg += (loop_count*30) / (ft_t * 1000000000);

}

// Thread Structure for IOPs
struct ith
{
	int lc, th_counter;
	int ia, ib, ic, id;
	pthread_t threads;
};

// IOPs Benchmark
void *IAdd(void *data)
{
	struct ith *th_d;
	th_d = (struct ith *) data;

	for(th_d->lc = 1; th_d->lc <= l_c; th_d->lc++)
	{
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		th_d->ia + th_d->id;
		th_d->ia + th_d->ib;
		th_d->ib + th_d->ic;
		th_d->ia - th_d->ib;
		
	}
}

void IOPSBenchmark()
{
	int k, v, n;
	double is_t, ie_t, it_t;
	struct ith it[th_count];

	for(k =0; k < th_count; k++)
	{
		it[k].lc = 1;
		it[k].th_counter = 1;
		it[k].ia = 1;
		it[k].ib = 2;
		it[k].ic = 0;
		it[k].id = 0;
	}

	gettimeofday(&t, NULL);
	is_t = t.tv_sec+(t.tv_usec/1000000.0);

	for(v = 0; v < th_count; v++)
	{
		pthread_create(&it[v].threads,NULL, &IAdd, (void *)&it[v]);
	}
	for(n =0; n < th_count; n++)
	{
		pthread_join(it[n].threads, NULL);
	}
	
	gettimeofday(&t, NULL);
	ie_t = t.tv_sec+(t.tv_usec/1000000.0);
	it_t = ie_t - is_t;
	i_avg += (loop_count*30) / (it_t * 1000000000);

}

int main(int argc, char *argv[])
{
	loop_count = atoi(argv[1]); // loop count
	th_count = atoi(argv[2]); // thread count
	l_c = loop_count/th_count; // Sharing the operations across the threads
	f_avg = 0;
	i_avg = 0;
	int h;

	if (argc < 2){
        printf("Incorrect number of parameters. Correct usage is mentioned below.\n");
        printf("./[objectname] [operation count] [thread count]\n");
        exit(1);
    }
	
	printf("\nStarting CPU Benchmark...\n");
	printf("\nThreads Implemented: %ld \n", th_count);
	
	// FLOPs Benchmark
	printf("\nComputing CPU-FLOPs Performance...\n");
	for(h = 1; h <= 5; h++)
	{
		FLOPSBenchmark();
	}
	printf("Number of FLOPs: %lf G-FLOPs\n", f_avg/5);
	sleep(2);

	// IOPs Benchmark
	printf("\nComputing CPU-IOPs Performance...\n");
	for(h = 1; h <= 5; h++)
	{
		IOPSBenchmark();
	}
	printf("Number of IOPs: %lf G-FLOPs\n", i_avg/5);
	printf("\nEnding...\n");

	return 0;
}
