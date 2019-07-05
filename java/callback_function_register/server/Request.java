// This class define the data format of requests.

public final class Request
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

