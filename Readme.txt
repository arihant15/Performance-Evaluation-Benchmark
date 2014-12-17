1. CPU Benchmark
	
	The CPU Benchmark is written using C programming language. Below are the steps to be followed to execute and run the program.
	
	1.1	File name “CPUBenchmark.c” contains the source code
	1.2	To complie the source code follow the below procedure
			
			$ gcc -pthread -o CPUBenchmark CPUBenchmark.c
		
	1.3	The output of the above command generates a file with name “CPUBenchmark”
	1.4	To execute the program, follow the below steps.

			$ ./CPUBenchmark <loop_count> <thread_count>

		loop_count - Indicates the number of times the FLOPs and IOPs to be performed.
	
		thread_count - Indicates the number of threads to be implemented in the program.

			eg: $ ./CPUBenchmark 100000000 1
		
		The above example will perform 100000000 FLOPs and IOPs using 1 thread.

	1.5	This outputs the computation speed of the CPU in terms of Giga FLOPS and Giga IOPs.  

			eg: $ ./CPUBenchmark 100000000 1

			Starting CPU Benchmark...

			Threads Implemented: 1

			Computing CPU-FLOPs Performance...
			Number of FLOPs: 4.179169 G-FLOPs

			Computing CPU-IOPs Performance...
			Number of IOPs: 4.150879 G-FLOPs

			Ending…

2. GPU Benchmark

	The GPU Benchmark is written using CUDA C programming language. Below are the steps to be followed to execute and run the program.

	2.1	File name “GPUBenchmark.cu” contains the source code
	2.2	To complie the source code follow the below procedure

			$ nvcc -o GPUBenchmark GPUBenchmark.cu

	2.3	The output of the above command generates a file with name “GPUBenchmark”
	2.4	To execute the program, follow the below steps.

			$ ./GPUBenchmark <loop_count>

		loop_count - Indicates the number of times the FLOPs and IOPs to be performed.

			eg: $ ./GPUBenchmark 10000

		The above example will perform 100000000 FLOPs and IOPs using 1 thread.

	2.5	This outputs the computation speed of the GPU in terms of Giga FLOPS and Giga IOPs and also, the memory read and write bandwidth with different size 		messages ( 1B, 1KB, 1MB). (Takes about 6 minutes).

			eg:$ ./GPUBenchmark 10000
			CUDA Device Query...
			There are 1 CUDA devices.
			CUDA Device #1
			CUDA Capability <Major.Minor> version number:     2.0
			15 Multiprocessors, 32 CUDA Cores/MP:     480 CUDA Cores
			Total amount of Global memory:               1 GBytes
			GPU Clock Rate: 1401 MHz (1.40 GHz)
			Starting FLOPs Benchmark...
			Number of FLOPs: 909.135815 G-FLOPs
			Starting IOPs Benchmark...
			Number of IOPs: 909.135801 G-IOPs
			Starting Memory Benchmark...
			1 Byte/Sec Message Size: 0.003180 GBps
			1 KByte/Sec Message Size: 3.197439 GBps
			1 MByte/Sec Message Size: 3244.668319 GBps
			Ending...
3. Memory Benchmark

	The CPU Benchmark is written using C programming language. Below are the steps to be followed to execute and run the program.

	3.1	The filename ‘Membenchmark.c’ contains the source code.

	3.2	To compile the source file type “ $ gcc -pthread MemBenchmark.c”

	3.3	In order to execute type “ ./a.out “

	3.4	Enter the number of threads to be used (1 thread/2 threads)

	3.5	Enter the buffer size to be used  (1byte/ 1Kb / 1 Mb)

	3.6	Wait for the result which displays throughput and latency.
     
			Sample Input Output :
			$ gcc -pthread MemBenchmark.c
			$ ./a.out
			Enter the number of threads you want to create:1
			Enter the size(1 byte/1024 bytes/1048576 bytes:1024
			Constructing the file...
			Time elapsed using threads: 0.000974 Sec
			Throughput for seq read = 5133.787026 
			Time elapsed using threads: 0.001670 Sec
			Throughput for seq write = 2993.793005 
			Time elapsed using threads: 0.000810 Sec
			Throughput for rand read = 6173.541360 
			Time elapsed using threads: 0.001127 Sec
			Throughput for rand write =4436.539031 
			Ending...
			Latency: 4.763300 ns

 
4. DISK
		Code for Disk Benchmark is written in java. Steps to perform the experiments are as follows.

		4.1	Compile
			  $javac  ChannelOps.java 
			  $javac  MarkDisk.java
	
		4.2	Execute
			  $java MarkDisk
			<output>
				Enter Read Pattern
			        1)SequentialRead 2)RandomRead 
			        3)Sequential Write 4)Random Write. 
			</output>

		4.3	Input Read Pattern

		4.4	Enter the path to the file which you want to read
			<output>
			Enter FilePath
			<output>

		4.4	No of Thread
			Enter no of threads you want to execute for the operation

			<Sample Output>
				#### Disk BenchMark  ####
				Performing disk read operation for....buffer size=1 B
				##Thread started for operation seqRead
				###Benchmark For ThreadThread0001
				###Thread0011  complete for operation seqRead
				 1byte   	 1kbyte 	 1mbyte 	 
				 0.0		 331.0		 2832.0		
			</Sample Output>

		4.5     Repeat from step 4.2 for other operations.

5. Network Benchmark

	5.1 TCP

		In order to run network benchmark we are required to execute 2 java files

 			1.NetworkServer.class 
			2.NetworkClient.class

		Here are the steps to follow:

		5.1.1	Open 2 terminal windows

			5.1.1.1	Locate  and execute NetworkServer.class 

					java NetworkServer

					On successful execution it prints

					<output>Listner created</output>

			5.1.2	Locate and execute NetworkClient.class

					java NetworkClient

					On successful execution it prints

					<output>Socket Created
					1. Calculate network latency
					2. Calculate Bandwidth over the Loopback
					0. Exit
					</output>
					To calculate latency press 1

					To calculate Bandwidth press 2

			            	<output>  Enter buffer Size(1/1024/65536)
					</output>

	5.2 UDP

		As TCP this modules also uses 2 files for benchmark test

			1.UDPClient.class 
			2.DatagramServer.class

		Here are the steps to follow:

		5.2.1	Open 2 terminal windows

			5.2.1.1	Locate  and execute DatagramServer.class 
				a.	java DatagramServer
				b.	On successful execution it prints 

						<output>Listner created</output>

			5.2.2.1	Locate and execute UDPClient.class
				a.	java UDPClient.class 
				b.	On successful execution it prints

						<output>Socket Created
						1. Calculate network latency
						2. Calculate Bandwidth over the Loopback
						0. Exit </output>
			5.2.2.2	Follow Steps 3.3 and 3.4 same as under 5.1(TCP)

	

