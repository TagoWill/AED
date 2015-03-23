import java.awt.Color;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/* Arvores Vermelhas e Pretas */
public class ProblemaC {
	static int exist=0;
	static No tree = null;
	public static void main (String[] args) throws IOException
	{
			BufferedReader bi = new BufferedReader(new InputStreamReader(System.in));
			String line;

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
						tree = insertNo(line, "I", tree, null);
					}else {
						line = line.replace(" R", "");
						tree = insertNo(line, "R", tree, null);
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
	
	public static No insertNo(String s, String e, No novoNo, No father)
    {
	   if(novoNo == null)
	   {
		   novoNo = new No(s, e, Color.red, father);
	   } else if (novoNo.matricula.compareToIgnoreCase(s) == 0){
	    	   novoNo.count++;
	    	   novoNo.estado = e;
	   }
	   else if (novoNo.matricula.compareToIgnoreCase(s) < 0)
       {
		   novoNo.left = insertNo(s, e, novoNo.left, novoNo);
       }
       else if (novoNo.matricula.compareToIgnoreCase(s) > 0)
       {
    	   novoNo.right = insertNo(s, e, novoNo.right, novoNo);
       }
	   changeColors(novoNo);
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
		} else {
			novoNo.right = unflagNo(s, novoNo.right);
		}
		return novoNo;
	  }
    
    public static void changeColors(No novoNo) {
        // Step 1: color the node red
        setColor(novoNo, Color.red);

        // Step 2: Correct double red problems, if they exist
        if (novoNo != null && novoNo != tree && isRed(novoNo.father)) {

            // Step 2a (simplest): Recolor, and move up to see if more work
            // needed
            if (isRed(siblingOf(novoNo.father))) {
                setColor(novoNo.father, Color.black);
                setColor(siblingOf(novoNo.father), Color.black);
                setColor(novoNo.father.father, Color.red);
                changeColors(novoNo.father.father);
            }

            // Step 2b: Restructure for a parent who is the left child of the
            // grandparent. This will require a single right rotation if n is
            // also
            // a left child, or a left-right rotation otherwise.
            else if (novoNo.father == leftOf(novoNo.father.father)) {
                if (novoNo == rightOf(novoNo.father)) {
                    llBalance(novoNo = novoNo.father);
                }
                setColor(novoNo.father, Color.black);
                setColor(novoNo.father.father, Color.red);
                lrBalance(novoNo.father.father);
            }

            // Step 2c: Restructure for a parent who is the right child of the
            // grandparent. This will require a single left rotation if n is
            // also
            // a right child, or a right-left rotation otherwise.
            else if (novoNo.father == rightOf(novoNo.father.father)) {
                if (novoNo == leftOf(novoNo.father)) {
                    rrBalance(novoNo = novoNo.father);
                }
                setColor(novoNo.father, Color.black);
                setColor(novoNo.father.father, Color.red);
                rlBalance(novoNo.father.father);
            }
        }

        // Step 3: Color the root black
        setColor((No) tree, Color.black);
    }
    
    public static No leftOf(No n) {
        return n == null ? null : (No) n.left;
    }

    public static No rightOf(No n) {
        return n == null ? null : (No) n.right;
    }
    
    private static No siblingOf(No n) {
        return (n == null || n.father == null) ? null : (n == n
                .father.right) ? (No) n.father.right
                : (No) n.father.left;
    }
    
    public static boolean isRed(No n) {
        return n != null && colorOf(n) == Color.red;
    }
    
    public static Color colorOf(No n) {
        return n == null ? Color.black : n.cor;
    }
    
    public static void setColor(No novoNo, Color c) {
        if (novoNo != null)
            novoNo.cor = c;
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
      No father;
      No left;
      No right;
      int count;
      public int height, leftHeight, rightHeight;
      Color cor;

      No(){
    	  matricula = null;
    	  estado = null;
    	  father = null;
          left = null;
          right = null;
          count = 0;
          height = 0;
          leftHeight = 0;
          rightHeight = 0;
          cor = Color.RED;
  	  }
      
      No(String matricula, String estado, Color cor, No father) {
         this.matricula = matricula;
         this.estado = estado;
         this.cor = cor;
         this.father = father;
         left = null;
         right = null;
         count = 1;
         height = 0;
         leftHeight = 0;
         rightHeight = 0;
      }
      
      public void resetHeight()
      {
    	  leftHeight = ProblemaC.getHeight(left);
    	  rightHeight = ProblemaC.getHeight(right);
    	  height = 1 + Math.max(leftHeight, rightHeight);
      }
}
