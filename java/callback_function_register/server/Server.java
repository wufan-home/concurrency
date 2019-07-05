import java.util.concurrent.ConcurrentLinkedQueue; 

public class Server
{
    private ConcurrentLinkedQueue<Request> requestQueue;

    private boolean isEventTriggered;

    private boolean isServerLaunched;

    public void execute()
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
    }

    public void untrigger()
    {
        isEventTriggered = false;
    }

    public void launch()
    {
        System.out.println("The server has been launched...");

        isServerLaunched = true;
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
