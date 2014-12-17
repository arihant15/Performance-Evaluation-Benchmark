
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class DatagramServer {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DatagramSocket ds=null;
			try {
				while(true)
				{
					ds= new DatagramSocket(9090);
					
					System.out.println("datagram socket created");
					byte []buff= new byte[256];
					DatagramPacket dp=new DatagramPacket(buff, buff.length);
					ds.receive(dp);
					String data=new String(dp.getData(), 0, dp.getLength());
					InetAddress address = dp.getAddress();
					int port = dp.getPort();
					dp = new DatagramPacket(data.getBytes(), (data.getBytes()).length, address, port);
					System.out.println("sending data");
					ds.send(dp);
					ds.close();
				}
				
			} catch (SocketException e) {
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

}
