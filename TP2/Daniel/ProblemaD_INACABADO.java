import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;


public class ProblemaD {
	static int exist=0;
	public static void main (String[] args) throws IOException
	{
		BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
		String line;
		RandomTree tree = new RandomTree();

		line = bi.readLine();
		while (!line.equalsIgnoreCase(""))
		{
			exist=0;
			if(line.startsWith("PASS"))
			{
				line = line.replace("PASS ", "");
				if(line.endsWith("I"))
				{
					line = line.replace(" I", "");
					if(!tree.verificar(tree.getRaiz(), line, "I")){
						tree.insertNo(tree.getRaiz(), line, "I");
					}
				}else {
					line = line.replace(" R", "");
					
					if(!tree.verificar(tree.getRaiz(), line, "R")){
						tree.insertNo(tree.getRaiz(), line, "R");
					}
				}
			} else if(line.startsWith("UNFLAG"))
			{
				line = line.replace("UNFLAG ", "");
				if(tree.locateNo(tree.getRaiz(), line) == true)
				{
					try {
						tree.unflag(line);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			} else if(line.startsWith("STATUS"))
			{
				line = line.replace("STATUS ", "");
				tree.printNos(tree.getRaiz(), line);
				if(exist==0)
					System.out.println(line + " NO RECORD");
			}
			line = bi.readLine();
		}
	}
}

class RandomTree
{
	private No raiz;
	private double rand;
	public int nos=0, rd=0, re=0;
	private Random r = new Random();
	
	public void insertNo(No novoNo, String s, String e)
	{		
		novoNo = new No(s, e);
		if(this.raiz!=null)
		{
			calculaTam();
		}
		this.raiz = insere(novoNo, this.raiz);
	}
	
	public void calculaTam(){
		this.raiz.size = calculaTamanho(this.raiz);
	}
	
	public int calculaTamanho(No node)
	{
		int tamEsq=0, tamDir=0, tamanho;
		if (node.left!=null) {
			tamEsq = calculaTamanho(node.left);
		}
		if (node.right!=null) {
			tamDir = calculaTamanho(node.right);
		}
		tamanho = tamEsq + tamDir + 1;
		node.size = tamanho;
		return tamanho;
	}

	public No insere(No novo, No anterior)
	{
		if(anterior==null){
			anterior=novo;
			return anterior;
		}
		else{
			rand=r.nextDouble();
			double tam=anterior.size;
			double prob=(1/(tam+1));
			if(rand>=prob){	
				insereRaiz(novo, anterior);
				return novo;
			}
			else if(novo.matricula.compareToIgnoreCase(anterior.matricula) < 0){
				anterior.left=insere(novo,anterior.left);
			}
			else{
				anterior.right=insere(novo,anterior.right);
			}
			return anterior;
		}
	}

	public void insereRaiz(No novo, No node){
		if(node!=null){
			if(novo.matricula.compareToIgnoreCase(node.matricula) < 0){
				novo=insereN(novo,node,node.matricula, node.estado);
			}
			else{
				novo=insereN(novo,node,node.matricula, node.estado);
			}
			if(node.left!=null){
				insereRaiz(novo, node.left);
			}
			if(node.left!=null){
				insereRaiz(novo, node.left);
			}
		}
	}

	public No insereN(No node, No aux, String t, String e)
	{
		if(node==null){
			node = new No(t, e);
			node.count = aux.count;
		}
		else{
			if(t.compareTo(node.matricula) < 0){
				node.left=insereN(node.left, aux, t, e);
			}
			else{
				node.right=insereN(node.right, aux, t, e);
			}
		}
		return node;
	}

	public boolean verificar(No node, String word, String e){
		if(node==null){
			return false;
		}
		else{
			if(word.compareTo(node.matricula)==0){
				node.count++;
				node.estado = e;
				return true;
			}
			else if(word.compareTo(node.matricula)<0){
				return verificar(node.left, word, e);
			}
			else{
				return verificar(node.right, word, e);
			}
		}
	}
	
	public boolean locateNo(No node, String word){
		if(node==null){
			return false;
		}
		else{
			if(word.compareToIgnoreCase(node.matricula)==0){
				return true;
			}
			else if(word.compareToIgnoreCase(node.matricula)<0){
				return locateNo(node.left, word);
			}
			else{
				return locateNo(node.right, word);
			}
		}
	}

	public void unflag(String s) throws Exception
	{
		this.raiz = unflagNo(s, this.raiz);
		if(this.raiz!=null){
			calculaTam();
		}
	}
    
    public No unflagNo(String s, No novoNo)
    {
    	if(novoNo==null) return null;
		if(novoNo.matricula.compareToIgnoreCase(s) == 0)
		{
			No tmp;
			tmp=escolhe(novoNo.left,novoNo.right);	
			novoNo=tmp;
			novoNo.estado = "R";
		}else if(novoNo.matricula.compareToIgnoreCase(s) < 0)
		{
			novoNo.left = unflagNo(s, novoNo.left);
		} else {
			novoNo.right = unflagNo(s, novoNo.right);
		}
		return novoNo;
	}
	
    public No escolhe(No esquerda, No direita){
		double n,tamaux;

		if(esquerda==null && direita!=null){
			return direita;
		}
		else if(direita==null && esquerda!=null){
			return esquerda;
		}
		else if(esquerda!=null && direita!=null){

			n=esquerda.size+direita.size;
			tamaux=esquerda.size;
			if(Math.random()*n < 1.0*tamaux){
				esquerda.right=escolhe(esquerda.right,direita);
				return esquerda;
			}
			else{
				direita.left=escolhe(esquerda,direita.left);
				return direita;
			}
		}
		else{
			return null;
		}
	}
    
	public No getRaiz()
	{
		return raiz;
	}

	public void setRaiz(No raiz) 
	{
		this.raiz = raiz;
	}	
	
	public void printNos(No tree, String line)
    {
    	if(tree != null)
    	{
			printNos(tree.right, line);
			if(tree.matricula.compareToIgnoreCase(line) == 0)
			{
				System.out.println(tree.matricula + " " + tree.count + " " + tree.estado);
				ProblemaD.exist=1;
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
      int count, size;

      No(){
    	  matricula = null;
    	  estado = null;
          left = null;
          right = null;
          count = 1;
          size = 1;
  	  }
      
      No(String matricula, String estado) {
         this.matricula = matricula;
         this.estado = estado;
         left = null;
         right = null;
         count = 1;
         size = 1;
      }
}
