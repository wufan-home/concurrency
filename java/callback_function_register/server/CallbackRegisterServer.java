public class CallbackRegisterServer
{
    public void register_function()
    {

    }
    
    public void register_callback()
    {
        // This function is to register objects which
        // provide callback functions.
    }

    public static void main(String[] args)
    {
        // System.out.println("Start the program CallbackRegisterServer");
        
        Runnable task = () -> {
            String threadName = Thread.currentThread().getName();
            System.out.println("Hello " + threadName);
        };

        task.run();

        Thread thread = new Thread(task);
        thread.start();

        System.out.println("Done!");


        // System.out.println("Stop the program CallbackRegisterServer");
    }
}
