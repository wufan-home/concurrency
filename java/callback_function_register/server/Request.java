public class Request
{
    private String mContext;

    Request(final String context)
    {
        mContext = context;
    }

    public void callback()
    {
        System.out.println(mContext);
    } 
}

