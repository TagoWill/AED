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
		int n1=0, n2=0, i, j, k;
			
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
		        for (k=numberofwords; k<numberofwords+splited.length; k++) 
		        {
		        	splited[k-numberofwords] = splited[k-numberofwords].replaceAll("[.:,?!]","");
		        	p[k] = new Palavra(splited[k-numberofwords]);
		        }
		        numberofwords = numberofwords + splited.length;
			}
			line = bi.readLine();
		}
		
		removewords(palavrasligacao, p);
		
		sortwords(p);
		
		countwords(p);
		
		while(most_repeated!=0)
		{
			printwords(p, most_repeated);
			most_repeated--;
		}
	}

	private static void removewords(String[] palavrasligacao, Palavra[] palavras)
	{
		int i, j, k;
		for(i=0; i<palavrasligacao.length; i++)
		{
			for(j=0; j<numberofwords; j++)
			{
				if(palavras[j].pal.equalsIgnoreCase(palavrasligacao[i]))
				{
					for(k=j+1; k<numberofwords; k++)
					{
						palavras[j].pal=palavras[k].pal;
					}
					numberofwords--;
				}
			}
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
	    
	    for(i=0; i<numberofwords; i++)
	    {
	    	int lol=i;
	    	if(i+1 < numberofwords)
	    	{
	    		if(p[i].pal.equalsIgnoreCase(p[i+1].pal))
	    		{
	    			for (j=i+2; j<numberofwords; j++)
	    			{
	    				p[lol+1].pal = p[j].pal;
	    				p[lol+1].contador = p[j].contador;
	    				lol++;
	    			}
	    			numberofwords--;
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