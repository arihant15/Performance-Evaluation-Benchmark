
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Scanner;

import com.service.BenchMarkHelper;

public class UDPClient {

	public static void main(String[] args) {
		DatagramSocket ds=null;
		try {
			String userInput;
			long t1,t2;
			float a[]=new float[1024*64];
			Scanner stdin = new Scanner(System.in);
			System.out.println("Press 1");
			UDPClient uc= new UDPClient();
			uc.showMenu();
			InetAddress address = InetAddress.getByName("localhost");
			DatagramPacket dp=null;
			while((userInput=uc.askUser("Choose One option"))!=null){
				switch (userInput)
				{
					case "1":	ds=new DatagramSocket();
								byte[] buf=new byte[256];
								dp = new DatagramPacket(buf, buf.length,address, 9090);
									t1=System.nanoTime();
									ds.send(dp);
									t2=(System.nanoTime()-t1)/1000;
								System.out.println("Latency in microsec " + t2);
								break;
								
					case "2":  	
								int buffer=Integer.parseInt(uc.askUser("Enter buffer Size(1/1024/65536)"));
								ds=new DatagramSocket();
								System.out.println("buffer is :"+buffer);
									//created random value
									byte []temp="this is sime random dataa".getBytes();
									temp=BenchMarkHelper.getByteArray(buffer);
									dp = new DatagramPacket(temp, temp.length,address, 9090);
									System.out.println("dp created");
									t1=System.currentTimeMillis();
									ds.send(dp);
									System.out.println("datasend");
									dp = new DatagramPacket(temp, temp.length,address, 9090);
									ds.receive(dp);
									t2=(System.currentTimeMillis()-t1);
								System.out.println(t2);
								//t2=(long) BenchMarkHelper.computeSum(a);
								String s=new String(dp.getData(), 0, dp.getLength());
								System.out.println("time taken"+t2);
								System.out.println("total data transferred:"+buffer);
								double d1=(buffer)/t2;
								System.out.println("throughput in bytes per millisec:"+d1);
								float th=(float) ((d1*1000*8)/(1024*1024));
								System.out.println("Throughput  Mbits/sec :"+th);
								break;
											
					default:  break;
				}					
			}	
			
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally
		{
			ds.close();
		}
		

	}
	
	public void showMenu()
	{
		System.out.println("1. Calculate network latency");
		System.out.println("2. Calculate Bandwidth over the Loopback");
		System.out.println("0. Exit");
		
	}
	public String askUser(String q)
	{
		 System.out.println(q);
		 Scanner reader = new Scanner(System.in);
		 String resp=reader.nextLine();
		return resp.trim();
	}
	
}
