
import java.io.Console;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class MarkDisk {
	
	/**
	 * @param args
	 */
	
	
	public static void main(String args[])
	{
	try {
		System.out.println("\n #### Disk BenchMark  ####\n\n");
		float benchmark[]= new float[3];
		String filePath=null;
		//Environment details
		System.out.println("Free memory (bytes): " + 
		 Runtime.getRuntime().freeMemory());
		 System.out.println("total memory"+Runtime.getRuntime().totalMemory());
		System.gc();
		 
		 //User Input
		 MarkDisk md=new MarkDisk();
		 
		 int size=0;
		 ChannelOps cOps= new ChannelOps();

		 String readPattern=md.askUser("Enter ReadPattern 1)SequentialRead 2)RandomRead 3)Sequential Write 4)Random Write. \n");
		 int t=1;
		 switch(readPattern)
		 {
		 case "1":	filePath= md.askUser("Enter FilePath \n");
		 			System.out.println("reading system path "+filePath);
		 			t=Integer.parseInt(md.askUser("No oF Thread \n"));
		 			benchmark=cOps.squentialOps(filePath,t);
		 			break;
		 		
		 case "2":	filePath= md.askUser("Enter FilePath \n");		 
		 			System.out.println("reading system path "+filePath);
		 			t=Integer.parseInt(md.askUser("No oF Thread \n"));
		 			cOps.randomOps(filePath,t);
		 			break;		
		 case "3":	benchmark=cOps.writeOps(false);break;
		 
		 case "4":	benchmark=cOps.writeOps(true);break;
		 
		 default : System.out.println("\t NO option selected \n\n");
		 		System.exit(0);break;
		 }
		
	} catch (Exception e) {
		e.printStackTrace();
	}
	}
	
	public String askUser(String q)
	{
		 System.out.println(q);
		 Scanner reader = new Scanner(System.in);
		 String resp=reader.nextLine();
		return resp.trim();
	}
	
	
}	
