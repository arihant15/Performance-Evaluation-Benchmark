
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class NetworkClient {
	
	
	public static void main(String arg[])
	{
	try {
		Thread t1=new Thread(new TcpHelper(),"t1");
		t1.start();
				} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			
		}
	
	}
	
	public void showMenu()
	{
		System.out.println("1. Calculate network latency");
		System.out.println("2. Calculate Bandwidth over the Loopback");
		System.out.println("0. Exit");
		
	}
	
	public float computeAverage(float []a,int n)
	{
	float sum=0;
		if(a!=null && a.length>0)
		{
			for(int j=0;j<a.length;j++)
			{
				sum+=a[j];	
			}
		}
		return sum/n;
	}
	public float computeSum(float []a)
	{
	float sum=0;
		if(a!=null && a.length>0)
		{
			for(int j=0;j<a.length;j++)
			{
				sum+=a[j];	
			}
		}
		return sum;
	}
	 public long getRandomNo(long l)
	 {
		 return (long) (Math.random()*l);
		 	
	 }	
	 public byte[] getByteArray(int size)
	 { byte[] b=new byte[size];
		 for(int j=0;j<size;j++)
		 {
			 b[j]=(byte) getRandomNo(size);
		 }
		 return b;
	 }
	
}
class TcpHelper implements Runnable
{
	synchronized public void run()
	{	
		this.clientOPs();
	}
	synchronized public String clientOPs()
	{
		Socket p1=null;
		
		System.out.println("Socket created\n ");
		NetworkClient nc= new NetworkClient();
		nc.showMenu();
		long t1=0,t2=0;
		try {
			p1=new Socket("localhost",8989);
			String userInput;
			float a[]=new float[1024*64];
			Scanner stdin = new Scanner(System.in);
			PrintWriter out= new PrintWriter(p1.getOutputStream(),true);
			BufferedReader in =
			        new BufferedReader(
			            new InputStreamReader(p1.getInputStream()));
			
			while ((userInput = stdin.nextLine()) != null) {
				switch (userInput)
				{
					case "1":	
								for(int i=0;i<1000;i++)
								{t1=System.nanoTime();
									out.println(nc.getRandomNo(100));
									if(in.readLine()!=null)
									{
										a[i]= ((System.nanoTime()-t1)/1000);		
									}
									
								}
								System.out.println("Avg latency in microsec " + nc.computeAverage(a,1000));
								break;
					case "2":   System.out.println("Enter buffer Size(1/1024/65536)");
								int buff=stdin.nextInt();
								System.out.println("buffer is :"+buff);
								int n=10000;

								for(int i=0;i<n;i++)
								{ 
									byte temp[]=null;
									temp=nc.getByteArray(buff);						//created random value
									t1=System.currentTimeMillis();					//start timestamp
									out.println(temp);									//data sent
									in.readLine();										//data received
									t2=System.currentTimeMillis()-t1;					//time difference
									a[i]=t2;
								}
								t2=(long) nc.computeSum(a);
								System.out.println("time taken"+t2);
								System.out.println("toatal data transferred:"+(n*buff));
								//here array a[] is holding the list through put in bytes/millisec for a 10000 loopback
								double d1=(n*buff)/t2;
								System.out.println("throughput in bytes per millisec:"+d1);
								float th=(float) ((d1*1000*8)/(1024*1024));
								System.out.println("Throughput  Mbits/sec :"+th);
								
								break;
						
					default:	System.out.println("invalid input");System.exit(0);
								break;
					
				}
			}
		
		
	}catch(Exception e)
		{
		e.printStackTrace();
		}
		return null;

		
	}
}

