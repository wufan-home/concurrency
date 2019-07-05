import java.lang.*;
import java.util.Random;

public class TestSuit
{
    private static void runEventIsTriggeredBeforeRequestRegisterTest(final Server server, final int size)
    {
        server.trigger();

        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);

        Runnable requestSending = () -> {
            sim.send();
        };
        
        Thread tRequestSending = new Thread(requestSending);
        tRequestSending.start();

        try
        {
            Thread.sleep(size * 1000);
        }
        catch (Exception e)
        { }
    }

    private static void runEventIsTriggeredAfterRequestRegisterTest(final Server server, final int size)
    {
        Runnable triggering = () -> {
            try
            {
                Thread.sleep(1000 * size);
            }
            catch (Exception e)
            {}
            server.trigger();
        };

        Thread tTriggering = new Thread(triggering);
        tTriggering.start();

        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);

        Runnable requestSending = () -> {
            sim.send();
        };
    
        Thread tRequestSending = new Thread(requestSending);
        tRequestSending.start();

        try
        {
            Thread.sleep(size * 1000);
        }
        catch (Exception e)
        {}
    }

    private static void runEventIsTriggeredDuringRequestRegisterTest(final Server server, final int size)
    {
        final Random random = new Random();

        final int sleepTime = random.nextInt(1000 * (size - 1)) % (1000 * (size - 1) - 1 + 1) + 1;
        System.out.println(Integer.toString(sleepTime));

        Runnable triggering = () -> {
            try
            {
                Thread.sleep(sleepTime);
            }
            catch (Exception e)
            {}
            server.trigger();
        };

        Thread tTriggering = new Thread(triggering);
        tTriggering.start();

        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);

        Runnable requestSending = () -> {
            sim.send();
        };
    
        Thread tRequestSending = new Thread(requestSending);
        tRequestSending.start();

        try
        {
            Thread.sleep(size * 1000);
        }
        catch (Exception e)
        {}
    }

    public static void main(String[] args)
    {
        Server server = new Server();
        
        server.launch();

        Runnable executing = () -> {
            while (true)
            {
                server.execute();

                try
                {
                    Thread.sleep(1);
                    // System.out.println("Wait for 300 ms...");
                }
                catch (Exception e)
                {
                    System.out.println("Error Failed to trigger the event.");
                }
            }
        };

        Thread tExecute = new Thread(executing);
        tExecute.start();

        // runEventIsNotTriggeredTest(server, 10);
        
        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredBeforeRequestRegisterTest...");
        runEventIsTriggeredBeforeRequestRegisterTest(server, 10);

        server.untrigger();

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredDuringRequestRegisterTest...");
        runEventIsTriggeredDuringRequestRegisterTest(server, 20);

        server.untrigger();

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredAfterRequestRegisterTest...");

        runEventIsTriggeredAfterRequestRegisterTest(server, 10);

    }
}
