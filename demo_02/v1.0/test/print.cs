using System;
using System.IO;
using System.Text;
using System.Threading;
public class HelloWorld
{
    public static void Main()
    {
        //for(int i=0;i<30;i++){
        //    System.Console.WriteLine("----------------------"+i);
        //    Thread.Sleep(500);
        //}
         StreamReader sr = new StreamReader("C:/Users/mail/Desktop/Xflask_demo/v0.5/test/readuser.log",Encoding.UTF8);
         String line;
         while ((line = sr.ReadLine()) != null){
             Console.WriteLine(line.ToString());
             Thread.Sleep(500);
         }
    }
}