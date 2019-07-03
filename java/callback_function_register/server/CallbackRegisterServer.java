import java.lang.*;
import java.util.concurrent.ConcurrentLinkedQueue;

public class CallbackRegisterServer
{
    private final static class Request
    {
        private String mContext;

        Request(final String context)
        {
            mContext = context;
        }

        public String getContext()
        {
            return mContext;
        }

        public void callback()
        {
            System.out.println(mContext + " callback function is run.");
        }
    } 
    
    private static boolean eventIsTriggered = false;

    private static ConcurrentLinkedQueue<Request> concurrentLinkedQueue = new ConcurrentLinkedQueue<Request>();

    private static int size = 30; 
    
    public static void registerCallback(final Request request)
    {
        concurrentLinkedQueue.offer(request);
        System.out.println(request.getContext() + " is registered. " + Integer.toString(concurrentLinkedQueue.size()));
    }
    
    public static void executeCallback(final Request request)
    {
        request.callback();
    }

    public static void main(String[] args)
    {
        // System.out.println("Start the program CallbackRegisterServer");

        Runnable sendRequest = () -> {
            try 
            {
                for (int i = 0; i < size; ++i)
                {
                    Request request = new Request("test request " + Integer.toString(i));
                    Thread.sleep(1000);
                    registerCallback(request);
                }
            }
            catch (Exception e)
            {
                System.out.println("Error: Fail to sleep for 1000.");
            }
        };

        Thread threadRequest = new Thread(sendRequest);
        threadRequest.start();

        Runnable eventTrigger = () -> {
            try
            {
                Thread.sleep(4500);
                eventIsTriggered = true;
                System.out.println("The event is triggered.");
            }
            catch (Exception e)
            {
                System.out.println("Error Failed to trigger the event.");
            }
        };

        Thread threadEventTriggered = new Thread(eventTrigger);
        threadEventTriggered.start();

        Runnable executeCallbackRunnable = () -> {
            for(int i = 0; i < size; )
            {
                if(eventIsTriggered)
                {
                    if (concurrentLinkedQueue.size() > 0)
                    {
                        executeCallback(concurrentLinkedQueue.poll());
                        ++i;
                    }
                    else
                    {
                        System.out.println("The request queue is empty. Wait for more requests be pushed.");
                    }
                }
                else
                {
                    System.out.println("The event has not been triggered.");
                }

                try
                {
                    Thread.sleep(500);
                }
                catch (Exception e)
                {

                }
            }
        };

        Thread threadExecuteCallback = new Thread(executeCallbackRunnable);
        threadExecuteCallback.start();

        // System.out.println("Stop the program CallbackRegisterServer");
    }
}
