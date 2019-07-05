import java.util.Random;

public final class SimulateSendingRequest
{
    private int sizeOfRequests;

    private Random random; 

    private Server serverWrapper;

    private final static int min = 1;

    private final static int max = 999;

    public SimulateSendingRequest(final Server server, final int size)
    {
        sizeOfRequests = size;

        serverWrapper = server;

        random = new Random();
    }

    public void send()
    {
        if(serverWrapper == null)
        {
            System.out.println("The server is not correctly configured...");

            return;
        }

        for(int i = 0; i < sizeOfRequests; ++i)
        {
            if (serverWrapper.register(new Request(Integer.toString(i))) < 0)
            {
                System.out.println("The server is not properly launched...");

                return;
            }

            int sleepTime = random.nextInt(max) % (max - min + 1) + min;
            try
            {
                Thread.sleep(sleepTime);
                System.out.println("Sleep for " + Integer.toString(sleepTime) + " milliseconds...");
            }
            catch (Exception e)
            {
                System.out.println("Error: Failed to sleep for " + Integer.toString(sleepTime) + " milliseconds...");
            }
        }
    }
}
