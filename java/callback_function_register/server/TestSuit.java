import java.lang.*;
import java.util.Random;

public class TestSuit
{
    private static void runEventIsTriggeredBeforeRequestRegisterTest(final Server server, final int size)
    {
        server.trigger();
        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);
        sim.send();
    }

    private static void runEventIsTriggeredAfterRequestRegisterTest(final Server server, final int size)
    {
        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);
        sim.send();
        server.trigger();

        try
        {
            Thread.sleep(1000 * size);
        }
        catch (Exception e) {}
    }

    private static void runEventIsTriggeredDuringRequestRegisterTest(final Server server, final int size)
    {
        final Random random = new Random();

        final int round = random.nextInt(size / 2 == 0 ? 1 : size / 2);
        System.out.println(Integer.toString(round * 1000));

        Runnable triggering = () -> {
            try
            {
                Thread.sleep(round * 1000);
            }
            catch (Exception e)
            {}
            server.trigger();
        };

        Thread tTriggering = new Thread(triggering);
        tTriggering.start();

        SimulateSendingRequest sim = new SimulateSendingRequest(server, size);
        sim.send();
    }

    public static void main(String[] args)
    {
        Server server = new Server();
        
        Runnable serverRunning = () -> {
            server.launch();
        };

        Thread tServer = new Thread(serverRunning);
        tServer.start();

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredBeforeRequestRegisterTest...");

        try
        {
            Runnable test1Running = () -> {
                runEventIsTriggeredBeforeRequestRegisterTest(server, 10);
            };

            Thread tTest1 = new Thread(test1Running);
            
            tTest1.start();
            tTest1.join();
        }
        catch (Exception e) {}

        server.untrigger();

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredDuringRequestRegisterTest...");
        
        try
        {
            Runnable test2Running = () -> {
                runEventIsTriggeredDuringRequestRegisterTest(server, 20);
            };

            Thread tTest2 = new Thread(test2Running);
            tTest2.start();
            tTest2.join();
        }
        catch (Exception e) {}

        server.untrigger();

        System.out.println("");
        System.out.println("");
        System.out.println("runEventIsTriggeredAfterRequestRegisterTest...");

        try
        {
            Runnable test3Running = () -> {
                runEventIsTriggeredAfterRequestRegisterTest(server, 10);
            };

            Thread tTest3 = new Thread(test3Running);
            tTest3.start();
            tTest3.join();
        }
        catch (Exception e) {}

        server.terminate();
    }
}
