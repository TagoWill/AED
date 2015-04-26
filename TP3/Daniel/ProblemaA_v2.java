import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProblemaA {
	static int numberofwords=0;
	static int most_repeated=1;
	public static void main (String[] args) throws IOException
	{
		BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
		String line;
		String[] palavrasligacao = null;
		Palavra[] p = new Palavra[400];
		int n1=0, n2=0, i, j, l, remover=0, k;
	
		line = bi.readLine();
		while (!line.equalsIgnoreCase(""))
		{
			n1 = Integer.parseInt(line);
			palavrasligacao = new String[n1];
			for(i=0; i<n1; i++)
			{
				line = bi.readLine();
				palavrasligacao[i] = line.toLowerCase();
			}
			line = bi.readLine();
			n2 = Integer.parseInt(line);
			for(j=0; j<n2; j++)
			{
				line = bi.readLine();
				line = line.toLowerCase();
				String[] splited = line.split("\\s+");
		        for (k=0; k<splited.length; k++) 
		        {
		        	splited[k] = splited[k].replaceAll("[.:,?!()]","");
		        	remover=0;
					for(l=0; l<palavrasligacao.length; l++)
					{
						if(splited[k].equalsIgnoreCase(palavrasligacao[l]))
						{
							remover=1;
						}
					}
					if(remover==0)
					{
						p[numberofwords] = new Palavra(splited[k]);
						numberofwords++;
					}
		        }
			}
			line = bi.readLine();
		}
		
		sortwords(p);
		
		countwords(p);
		
		while(most_repeated!=0)
		{
			printwords(p, most_repeated);
			most_repeated--;
		}
	}
	
	private static void sortwords(Palavra[] p) {
		int i, j;
		String tmp;
	    for (i=0; i<numberofwords; i++)
	    {
	    	tmp = p[i].pal;
	    	for (j=0; j<numberofwords; j++)
	    	{
	    		if (i == j){
	    			continue;
	    		}
	    		int x = tmp.compareTo(p[j].pal);
	    		if (x < 0)
	    		{
	    			tmp = p[j].pal;
	    			p[j].pal = p[i].pal;
	    			p[i].pal = tmp;
	    		}
	    	}
	    }
	}
	
	private static void countwords(Palavra[] p) {
		int i, j;
		String tmp;
	    for (i=0; i<numberofwords; i++)
	    {
	    	tmp = p[i].pal;
	    	for (j=0; j<numberofwords; j++)
	    	{
	    		if (i == j){
	    			continue;
	    		}
	    		int x = tmp.compareTo(p[j].pal);
	    		if (x == 0)
	    		{
	    			p[j].contador++;
	    			if(p[j].contador>most_repeated)
	    				most_repeated=p[j].contador;
	    		}
	    	}
	    }
	}
	
	private static void printwords(Palavra[] p, int max) {
		int j;
		
		for(j=0; j<numberofwords; j++)
		{
			if(p[j].contador==max){
				System.out.println(p[j].pal+" "+p[j].contador);
				if(max>1)
				{
					j=j+p[j].contador;
				}
			}
		}
	}
}

class Palavra
{
	String pal;
	int contador;
	
	Palavra(String pal)
	{
		this.pal = pal;
		this.contador = 1;
	}
}