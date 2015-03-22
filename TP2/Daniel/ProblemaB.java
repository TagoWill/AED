import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/* Arvores AVL */
public class ProblemaB {
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
					if(locateNo(line, 0, tree) == 1)
					{
						tree = unflagNo(line, tree);
					}
				} else if(line.startsWith("STATUS"))
				{
					line = line.replace("STATUS ", "");
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
		   novoNo.leftHeight++;
		   novoNo.leftHeight = getHeight(novoNo.left);
		   novoNo.rightHeight = getHeight(novoNo.right);
		   if(Math.abs(novoNo.leftHeight - novoNo.rightHeight) == 2)
			   novoNo = avl(novoNo);
		   else
			   novoNo.resetHeight();
       }
       else if (novoNo.matricula.compareToIgnoreCase(s) > 0)
       {
    	   novoNo.right = insertNo(s, e, novoNo.right);
    	   novoNo.rightHeight++;
    	   novoNo.leftHeight = getHeight(novoNo.left);
		   novoNo.rightHeight = getHeight(novoNo.right);
		   if(Math.abs(novoNo.leftHeight - novoNo.rightHeight) == 2)
			   novoNo = avl(novoNo);
		   else
			   novoNo.resetHeight();
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
		{
			novoNo.left = unflagNo(s, novoNo.left);
			novoNo.leftHeight = getHeight(novoNo.left);
			novoNo.rightHeight = getHeight(novoNo.right);
			if(Math.abs(novoNo.leftHeight - novoNo.rightHeight) == 2)
				novoNo = avl(novoNo);
			else
				novoNo.resetHeight();
		} else {
			novoNo.right = unflagNo(s, novoNo.right);
			novoNo.leftHeight = getHeight(novoNo.left);
			novoNo.rightHeight = getHeight(novoNo.right);
			if(Math.abs(novoNo.leftHeight - novoNo.rightHeight) == 2)
				novoNo = avl(novoNo);
			else
				novoNo.resetHeight();
		}
		return novoNo;
	  }
    
    public static No avl(No tree)
    {
    	int rrHeight=0, rlHeight=0, llHeight=0, lrHeight=0;
    	tree.rightHeight = getHeight(tree.right);
    	tree.leftHeight = getHeight(tree.left);
    		
    	if(tree.rightHeight > tree.leftHeight)
    	{
    		No rightChild = tree.right;
    		rrHeight = getHeight(rightChild.right);
    		rlHeight = getHeight(rightChild.left);
    		if(rrHeight > rlHeight)
    			return rrBalance(tree);
    		else
    			return rlBalance(tree);
    	}
    	else
    	{
    		No leftChild = tree.left;
    		llHeight = getHeight(leftChild.left);
    		lrHeight = getHeight(leftChild.right);
    		if(llHeight > lrHeight)
    			return llBalance(tree);
    		else
    			return lrBalance(tree);
    	}
    }
    
    static int getHeight(No tree)
  	{
  		if(tree == null) return -1;
  		else return tree.height;
  	}
    
    public static No rrBalance(No bTree)
	{
		No rightChild = bTree.right;
		No rightLeftChild = rightChild.left;
		rightChild.left = bTree;
		bTree.right = rightLeftChild;
		bTree.resetHeight();
		rightChild.resetHeight();
		
		return rightChild;
	}
    
    public static No rlBalance(No bTree)
	{
		No root = bTree;
		No rNode = root.right;
		No rlNode = rNode.left;
		No rlrTree = rlNode.right;
		No rllTree = rlNode.left;
		
		rNode.left = rlrTree;
		root.right = rllTree;
		rlNode.left = root;
		rlNode.right = rNode;
		
		rNode.resetHeight();
		root.resetHeight();
		rlNode.resetHeight();
		
		return rlNode;
	}
    
    public static No llBalance(No bTree)
	{
		No leftChild = bTree.left;
		No lrTree = leftChild.right;
		leftChild.right = bTree;
		bTree.left = lrTree;
		bTree.resetHeight();
		leftChild.resetHeight();
		return leftChild;
	}
    
    public static No lrBalance(No bTree)
	{
		No root = bTree;
		No lNode = root.left;
		No lrNode = lNode.right;
		No lrlTree = lrNode.left;
		No lrrTree = lrNode.right;
		
		lNode.right = lrlTree;
		root.left = lrrTree;
		lrNode.left = lNode;
		lrNode.right = root;
		
		lNode.resetHeight();
		root.resetHeight();
		lrNode.resetHeight();
		
		return lrNode;
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
      public int height, leftHeight, rightHeight;

      No(){
    	  matricula = null;
    	  estado = null;
          left = null;
          right = null;
          count = 0;
          height = 0;
          leftHeight = 0;
          rightHeight = 0;
  	  }
      
      No(String matricula, String estado) {
         this.matricula = matricula;
         this.estado = estado;
         left = null;
         right = null;
         count = 1;
         height = 0;
         leftHeight = 0;
         rightHeight = 0;
      }
      
      public void resetHeight()
      {
    	  leftHeight = ProblemaB.getHeight(left);
    	  rightHeight = ProblemaB.getHeight(right);
    	  height = 1 + Math.max(leftHeight, rightHeight);
      }
}
