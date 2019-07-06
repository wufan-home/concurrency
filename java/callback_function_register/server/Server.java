import java.util.concurrent.ConcurrentLinkedQueue; 

public class Server
{
    private ConcurrentLinkedQueue<Request> requestQueue;

    private volatile boolean isEventTriggered;

    private volatile boolean isServerLaunched;

    private void execute()
    {
        while (true)
        {
            if (!requestQueue.isEmpty())
            {
                if (isEventTriggered)
                {
                    requestQueue.poll().callback();
                }
                else
                {
                    // System.out.println("WARNING: The event has not been triggered...");
                }
            }
            else
            {
                // System.out.println("WARNING: The request queue is empty...");
            }

            if (!isServerLaunched)
                break;

            try
            {
                Thread.sleep(100);
            }
            catch (Exception e) {}
        }
    }

    public int register(final Request request)
    {
        if (!isServerLaunched)
        {
            System.out.println("The server has not been launched...");

            return -1;
        }

        requestQueue.add(request);

        System.out.println(request.getContext() + " has been pushed into the queue to wait for executing the callback function...");

        return requestQueue.size();
    }

    public void trigger()
    {
        isEventTriggered = true;
        System.out.println("The event is triggered...");
    }

    public void untrigger()
    {
        isEventTriggered = false;

        System.out.println("The event is untriggered...");
    }

    public void launch()
    {
        System.out.println("The server has been launched...");

        isServerLaunched = true;
        
        Runnable executing = () -> {
            execute();
        };

        try
        {
            Thread tExecute = new Thread(executing);
            tExecute.start();
            tExecute.join();
        }
        catch (InterruptedException e) {}
    }
   
    public void terminate()
    {
        isServerLaunched = false;
        
        isEventTriggered = false;

        requestQueue.clear();

        System.out.println("The server has been terminated...");
    }

    public Server()
    {
        requestQueue = new ConcurrentLinkedQueue<Request>();

        isEventTriggered = false;

        isServerLaunched = false;
    }
}
