import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProblemaA {
	static int exist=0;
	public static void main (String[] args) throws IOException
	{
			BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
			String line;
			No tree = null;

			line = bi.readLine();
			while (!line.equalsIgnoreCase(""))
			{
				exist=0;
				if(line.startsWith("PASS"))
				{
					line = line.replace("PASS ", "");
					//System.out.println(line);
					if(line.endsWith("I"))
					{
						line = line.replace(" I", "");
						tree = insertNo(line, "I", tree);
					}else {
						line = line.replace(" R", "");
						tree = insertNo(line, "R", tree);
					}
				} else if(line.startsWith("UNFLAG"))
				{
					line = line.replace("UNFLAG ", "");
					//System.out.println(line);
					if(locateNo(line, 0, tree) == 1)
						tree = unflagNo(line, tree);
				} else if(line.startsWith("STATUS"))
				{
					line = line.replace("STATUS ", "");
					//System.out.println(line);
					printNos(tree, line);
					if(exist==0)
						System.out.println(line + " NO RECORD");
				}
				line = bi.readLine();
			}
	}
	
	public static No insertNo(String s, String e, No novoNo)
    {
	   if(novoNo == null)
	   {
			novoNo = new No(s, e);
	   } else if (novoNo.matricula.compareToIgnoreCase(s) == 0){
	    	   novoNo.count++;
	    	   novoNo.estado = e;
	   }
	   else if (novoNo.matricula.compareToIgnoreCase(s) < 0)
       {
		   novoNo.left = insertNo(s, e, novoNo.left);
       }
       else if (novoNo.matricula.compareToIgnoreCase(s) > 0)
       {
    	   novoNo.right = insertNo(s, e, novoNo.right);
       }
       return novoNo;
    }
    
    public static int locateNo(String s, int booleano, No novoNo)
    {
		if(novoNo != null && booleano == 0){
			if(novoNo.matricula.compareToIgnoreCase(s) == 0){
				booleano = 1;
			}else if(novoNo.matricula.compareToIgnoreCase(s) < 0){
				booleano = locateNo(s, booleano, novoNo.left);
			}else{
				booleano = locateNo(s, booleano, novoNo.right);
			}
		}
		return booleano;
	  }
    
    public static No unflagNo(String s, No novoNo)
    {
		if(novoNo.matricula.compareToIgnoreCase(s) == 0)
		{
			novoNo.estado = "R";
		}else if(novoNo.matricula.compareToIgnoreCase(s) < 0)
			novoNo.left = unflagNo(s, novoNo.left);
		else
			novoNo.right = unflagNo(s, novoNo.right);
		return novoNo;
	  }
    
    public static void printNos(No tree, String line)
    {
    	if(tree != null)
    	{
			printNos(tree.right, line);
			if(tree.matricula.compareToIgnoreCase(line) == 0)
			{
				System.out.println(tree.matricula + " " + tree.count + " " + tree.estado);
				exist=1;
			}
			printNos(tree.left, line);
		}
    }
}

class No
{
      String matricula;
      String estado;
      No left;
      No right;
      int count;

      No(){
    	  matricula = null;
    	  estado = null;
          left = null;
          right = null;
          count = 0;
  	  }
      
      No(String matricula, String estado) {
         this.matricula = matricula;
         this.estado = estado;
         left = null;
         right = null;
         count = 1;
      }
}