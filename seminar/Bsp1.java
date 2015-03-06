
import java.io.*;

public class Bsp1 {
	public static void main( String args[] ) {
		try {
			FileOutputStream fos = new FileOutputStream( new File("test.txt") );
		}
		catch( FileNotFoundException e ) {
		}
		
		int array[] = new int[10];
		for( int i = 0; i <= 10; i++ )
			array[i] = 0;
	}
}


