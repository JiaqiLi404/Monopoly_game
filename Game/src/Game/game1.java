package Game;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class game1 extends HttpServlet {  
	static double highestsco=0;
	public game1() {  
        super();  
    }  
  
    public void destroy() {  
        super.destroy(); 
    }  
  
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {  
  
        String sco=request.getParameter("sco");   
        sco=new String (sco.getBytes("ISO8859-1"),"UTF-8");
        System.out.println("����"+sco);  
        double value = Double.valueOf(sco.toString());
        if(highestsco>value&&(!sco.equals("-1"))){  
            //Ĭ�������ʹ�õ���iso8859����1���룬����������������û�е�ǰ�ַ�����ʹ�õ�ǰϵͳ��Ĭ�ϱ��룺GBK  
            response.getOutputStream().write(String.format("%.0f",highestsco).getBytes("utf-8"));  
            System.out.println(String.format("���ֵ%.0fû�и���",highestsco)); 
            
        }else if(!sco.equals("-1")){  
            response.getOutputStream().write(String.format("%.0f",value).getBytes("UTF-8"));  
            System.out.println(String.format("���������ֵ%.0f",value)); 
            highestsco=value;
        }  else {
        	response.getOutputStream().write(String.format("%.0f",highestsco).getBytes("UTF-8"));  
            System.out.println(String.format("���������ֵ%.0f",highestsco)); 
        }
    }  
  
  
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {  
        this.doGet(request, response);  
      
    }  

}

