import java.lang.Integer;
import java.util.List;
import java.util.ArrayList;
import java.lang.String;
import java.util.Stack;
import org.javatuples.*;

@SuppressWarnings("unchecked")
public class Run
{
    private Integer a  = null;
    private Stack<Pair<Integer, Integer>> st1 = new Stack<Pair<Integer, Integer>>(); 
    private Stack<Pair<Integer, Integer>> st2 = new Stack<Pair<Integer, Integer>>();
    private Stack<Pair<Integer, Integer>> st3 = null;

    Run()
    {
    }
    
    public void run()
    {
        for(int i = 0; i < 10; i++)
        {
            st1.push(new Pair<Integer, Integer>(i, i));
        }
    
        for(Pair<Integer, Integer> b : st1)
        {
            st2.push(b);
        }

        st3 = (Stack)st1.clone();
        
        for(int i = 0; i < 10; i++)
        {
            System.out.println("st1: " +st1.get(i).getValue0()+ " " +st1.get(i).getValue1());
        }
        
        for(int i = 0; i < 10; i++)
        {
            System.out.println("st2: " +st2.get(i).getValue0()+ " "+ st2.get(i).getValue1());
        }
       
        for(int i = 0; i < 10; i++)
        {
            System.out.println("st3: " +st3.get(i).getValue0()+ " " + st2.get(i).getValue1());
        }
    }
}
