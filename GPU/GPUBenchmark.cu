#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int devCount, cudaCores, smCount, totalThreads;
long loop_count;
double f_avg, i_avg;
size_t global_mem;
struct timeval t;

// From Device Query Example code
inline int _ConvertSMVer2Cores(int major, int minor)
{
    // Defines for GPU Architecture types (using the SM version to determine the # of cores per SM
    typedef struct
    {
        int SM; // 0xMm (hexidecimal notation), M = SM Major version, and m = SM minor version
        int Cores;
    } sSMtoCores;

    sSMtoCores nGpuArchCoresPerSM[] =
    {
        { 0x10,  8 }, // Tesla Generation (SM 1.0) G80 class
        { 0x11,  8 }, // Tesla Generation (SM 1.1) G8x class
        { 0x12,  8 }, // Tesla Generation (SM 1.2) G9x class
        { 0x13,  8 }, // Tesla Generation (SM 1.3) GT200 class
        { 0x20, 32 }, // Fermi Generation (SM 2.0) GF100 class
        { 0x21, 48 }, // Fermi Generation (SM 2.1) GF10x class
        { 0x30, 192}, // Kepler Generation (SM 3.0) GK10x class
        { 0x32, 192}, // Kepler Generation (SM 3.2) GK10x class
        { 0x35, 192}, // Kepler Generation (SM 3.5) GK11x class
        { 0x37, 192}, // Kepler Generation (SM 3.7) GK21x class
        { 0x50, 128}, // Maxwell Generation (SM 5.0) GM10x class
        {   -1, -1 }
    };
	    int index = 0;

    while (nGpuArchCoresPerSM[index].SM != -1)
    {
        if (nGpuArchCoresPerSM[index].SM == ((major << 4) + minor))
        {
            return nGpuArchCoresPerSM[index].Cores;
        }

        index++;
    }

    // If we don't find the values, we default use the previous one to run properly
    printf("MapSMtoCores for SM %d.%d is undefined.  Default to use %d Cores/SM\n", major, minor, nGpuArchCoresPerSM[index-1].Cores);
    return nGpuArchCoresPerSM[index-1].Cores;
}

// GPU FLOPS Benchmark

__global__ void FAdd(float *d_a, float *d_b, float *d_c, int totalThreads, long l_c)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i < totalThreads)
	{
		for (int j = 0; j < l_c; ++j)
		{
			d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_b[i] = d_b[i] + d_b[i];
		}
	}
}

void FLOPSBenchmark()
{
	float *fa, *fb, *fc;
	float *d_fa, *d_fb, *d_fc;
	double fs_t, fe_t, ft_t;
	
	fa = (float *)malloc(totalThreads*sizeof(float));
	fb = (float *)malloc(totalThreads*sizeof(float));
	fc = (float *)malloc(totalThreads*sizeof(float));

	cudaMalloc(&d_fa, totalThreads*sizeof(float));
	cudaMalloc(&d_fb, totalThreads*sizeof(float));
	cudaMalloc(&d_fc, totalThreads*sizeof(float));
	
	for(int i = 0; i < totalThreads; ++i)
	{
		fa[i] = 0.000001;
		fb[i] = 0.000001;
		fc[i] = 0.000001;
	}
	
	cudaMemcpy(d_fa, fa, totalThreads*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_fb, fb, totalThreads*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_fc, fc, totalThreads*sizeof(float), cudaMemcpyHostToDevice);
	
	gettimeofday(&t, NULL);
	fs_t = t.tv_sec+(t.tv_usec/1000000.0);
	
	FAdd<<< smCount, cudaCores >>>(d_fa, d_fb, d_fc, totalThreads, loop_count);
	
	cudaThreadSynchronize();
	
	gettimeofday(&t, NULL);
	fe_t = t.tv_sec+(t.tv_usec/1000000.0);
	ft_t = fe_t - fs_t;
	f_avg += (loop_count*smCount*cudaCores*totalThreads*10)/(ft_t*1000000000);

	free(fa);
	free(fb);
	free(fc);

	cudaFree(d_fa);
	cudaFree(d_fb);
	cudaFree(d_fc);

}

// GPU IOPS Benchmark

__global__ void IAdd(int *d_a, int *d_b, int *d_c, int totalThreads, long l_c)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	if (i < totalThreads)
	{
		for (int j = 0; j < l_c; ++j)
		{
			d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_c[i] = d_c[i] + d_c[i];
                        d_b[i] = d_b[i] + d_b[i];
                        d_a[i] = d_a[i] + d_a[i];
                        d_b[i] = d_b[i] + d_b[i];
		}
	}
}

void IOPSBenchmark()
{
	int *ia, *ib, *ic;
	int *d_ia, *d_ib, *d_ic;
	double is_t, ie_t, it_t;
	
	ia = (int *)malloc(totalThreads*sizeof(int));
	ib = (int *)malloc(totalThreads*sizeof(int));
	ic = (int *)malloc(totalThreads*sizeof(int));

	cudaMalloc(&d_ia, totalThreads*sizeof(int));
	cudaMalloc(&d_ib, totalThreads*sizeof(int));
	cudaMalloc(&d_ic, totalThreads*sizeof(int));
	
	for(int i = 0; i < totalThreads; ++i)
	{
		ia[i] = 1;
		ib[i] = 1;
		ic[i] = 1;
	}
	
	cudaMemcpy(d_ia, ia, totalThreads*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_ib, ib, totalThreads*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_ic, ic, totalThreads*sizeof(int), cudaMemcpyHostToDevice);

	gettimeofday(&t, NULL);
        is_t = t.tv_sec + (t.tv_usec / 1000000.0);
	
	IAdd<<< smCount, cudaCores >>>(d_ia, d_ib, d_ic, totalThreads, loop_count);
	
	cudaThreadSynchronize();
	
	gettimeofday(&t, NULL);
	ie_t = t.tv_sec + ( t.tv_usec / 1000000.0);
	it_t = ie_t - is_t;
	i_avg += (loop_count*smCount*cudaCores*totalThreads*10)/(it_t*1000000000);
	
	free(ia);
	free(ib);
	free(ic);

	cudaFree(d_ia);
	cudaFree(d_ib);
	cudaFree(d_ic);

}

// GPU Memory Benchmark

void MemBenchmark()
{
	char *ca, *cb;
	char *d_ca, *d_cb;
	long message_size = 1024*1024*1024;
	double ms_t, me_t, mt_t;
	
	ca = (char *)malloc(message_size*sizeof(char));
	cb = (char *)malloc(message_size*sizeof(char));
	
	for(int k = 0; k < message_size; ++k)
	{
		ca[k] = (char)((rand()%10)+97);
		cb[k] = '0';
	}
	
	// Sequential Read/Write
	for(int i=0; i<3; i++)
	{
		cudaMalloc(&d_ca, message_size*sizeof(char));
		cudaMalloc(&d_cb, message_size*sizeof(char));
		
		cudaMemcpy(d_ca, ca, message_size*sizeof(char), cudaMemcpyHostToDevice);
		
		if( i == 0)
		{
			gettimeofday(&t, NULL);
        		ms_t = t.tv_sec + (t.tv_usec / 1000000.0);
			for(int j = 0; j < message_size; ++j)
				cudaMemcpy(&d_cb[j], &d_ca[j], 1, cudaMemcpyDeviceToDevice);
			gettimeofday(&t, NULL);
        		me_t = t.tv_sec + ( t.tv_usec / 1000000.0);
        		mt_t = me_t - ms_t;
			printf("1 Byte/Sec Message Size: %f GBps\n", (message_size/(mt_t*1000000000)));
		}
		if( i == 1)
		{
			gettimeofday(&t, NULL);
                        ms_t = t.tv_sec + (t.tv_usec / 1000000.0);
			for(int j = 0; j < message_size; j += 1024)
				cudaMemcpy(&d_cb[j], &d_ca[j], 1024, cudaMemcpyDeviceToDevice);
			gettimeofday(&t, NULL);
                        me_t = t.tv_sec + ( t.tv_usec / 1000000.0);
                        mt_t = me_t - ms_t;
			printf("1 KByte/Sec Message Size: %f GBps\n", (message_size/(mt_t*1000000000)));
		}
		if( i == 2)
		{
			gettimeofday(&t, NULL);
                        ms_t = t.tv_sec + (t.tv_usec / 1000000.0);
			for(int j = 0; j < message_size ; j += (1024*1024))
				cudaMemcpy(&d_cb[j], &d_ca[j], (1024*1024), cudaMemcpyDeviceToDevice);
			gettimeofday(&t, NULL);
                        me_t = t.tv_sec + ( t.tv_usec / 1000000.0);
                        mt_t = me_t - ms_t;
			printf("1 MByte/Sec Message Size: %f GBps\n", (message_size/(mt_t*1000000000)));
		}
		cudaFree(d_ca);
		cudaFree(d_cb);
		sleep(1);
	}
	free(ca);
	free(cb);
}

int main(int argc, char *argv[])
{

	f_avg = 0;
	i_avg = 0;
	loop_count = atoi(argv[1]); // loop count
	cudaGetDeviceCount(&devCount);
	printf("\nCUDA Device Query...\n");
	
	// Check CUDA Device Present
	if( devCount == 0 )
	{
		printf("No CUDA device found, Ending...");
	}
	else
	{
		//CUDA Device Count
		printf("There are %d CUDA devices.\n", devCount);

		// Iterate through devices
		for (int i = 0; i < devCount; ++i)
		{
			cudaSetDevice(i);
			// Get device properties
			printf("\nCUDA Device #%d\n\n", (i+1));
			cudaDeviceProp devProp;
			cudaGetDeviceProperties(&devProp, i);
			smCount = devProp.multiProcessorCount;
			cudaCores = _ConvertSMVer2Cores(devProp.major, devProp.minor);
			totalThreads = smCount * cudaCores;
			global_mem = devProp.totalGlobalMem;
			printf("CUDA Capability <Major.Minor> version number:     %d.%d\n", devProp.major, devProp.minor);
			printf("%d Multiprocessors, %d CUDA Cores/MP:     %d CUDA Cores\n", smCount, cudaCores, totalThreads);
			printf("Total amount of Global memory:               %lu GBytes\n", global_mem/(1024*1024*1024));
			printf("GPU Clock Rate:	%.0f MHz (%0.2f GHz)\n", devProp.clockRate * 1e-3f, devProp.clockRate * 1e-6f);
			
			//FLOPS Benchmark
			printf("\nStarting FLOPs Benchmark...\n");
			for( int h = 1; h <= 5; h++)
			{
				FLOPSBenchmark();
			}
			printf("Number of FLOPs: %lf G-FLOPs\n", (f_avg/5));
			sleep(1);

			//IOPS Benchmark
			printf("\nStarting IOPs Benchmark...\n");
			for( int h = 1; h <= 5; h++)
			{
				IOPSBenchmark();
			}
			printf("Number of IOPs: %lf G-IOPs\n", (i_avg/5));
			sleep(1);

			//Memory Benchmark
			printf("\nStarting Memory Benchmark...\n");
			MemBenchmark();
			
			printf("\nEnding...\n");
			
		}
	}

	return 0;
}
