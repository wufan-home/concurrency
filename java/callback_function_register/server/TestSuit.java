import java.lang.*;

public class TestSuit
{
    private static void runEventIsTriggeredBeforeRequestRegisterTest(final Server server, final int size)
    {
        server.launch();
        
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
        // server.terminate();
    }

    private static void runEventIsTriggeredAfterRequestRegisterTest(final Server server, final int size)
    {
        server.launch();
    
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

        // server.terminate();
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
                    Thread.sleep(300);
                    System.out.println("Wait for 300 ms...");
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
        //
        //
        System.out.println("");
        System.out.println("runEventIsTriggeredBeforeRequestRegisterTest...");

        runEventIsTriggeredBeforeRequestRegisterTest(server, 10);

        server.untrigger();

        // runEventIsTriggeredDuringRequestRegisterTest(server, 10);

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredAfterRequestRegisterTest...");

        runEventIsTriggeredAfterRequestRegisterTest(server, 10);

    }
}
