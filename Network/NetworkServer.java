
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;

public class NetworkServer {
		public static void main(String args[]) throws Exception
		{String flag="true";
		Socket peerNode=null;
		String inputLine=null;
		String outputLine=null;
			ServerSocket peerListner=null;
			 try {
				 while(true)
				 {
				peerListner=new ServerSocket(8989);
				 System.out.println("Listner created");
				 peerNode=peerListner.accept();
				 System.out.println("accept connection");
				 int optionType=1;
				 PrintWriter out =
					        new PrintWriter(peerNode.getOutputStream(), true);
					    BufferedReader in = new BufferedReader(
					        new InputStreamReader(peerNode.getInputStream()));
					    while ((inputLine = in.readLine()) != null) {
					    	out.println(inputLine);
					        if (inputLine.equals("Bye."))
					            break;
					    	}
					 	    }
				
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					 finally{
						 peerNode.close();
					 }
					 
				 }

}
