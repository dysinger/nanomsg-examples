#include <assert.h>
//#include <libc.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/bus.h>

int node (const int argc, const char **argv)
{
    int sock = nn_socket (AF_SP, NN_BUS);
    assert (sock >= 0);
    assert (nn_bind (sock, argv[2]) >= 0);
    sleep (1); // wait for connections
    if (argc >= 3)
    {
        for(int x=3; x<argc; x++)
            assert (nn_connect (sock, argv[x]) >= 0);
    }
    sleep (1); // wait for connections
    int to = 100;
    assert (nn_setsockopt (sock, NN_SOL_SOCKET, NN_RCVTIMEO, &to, sizeof (to)) >= 0);
    // SEND
    int sz_n = strlen(argv[1]) + 1; // '\0' too
    printf ("%s: SENDING '%s' ONTO BUS\n", argv[1], argv[1]);
    int send = nn_send (sock, argv[1], sz_n, 0);
    assert (send == sz_n);
    while (1)
    {
        // RECV
        char *buf = NULL;
        int recv = nn_recv (sock, &buf, NN_MSG, 0);
        if (recv >= 0)
        {
            printf ("%s: RECEIVED '%s' FROM BUS\n", argv[1], buf);
            nn_freemsg (buf);
        }
    }
    return nn_shutdown (sock, 0);
}

int main (const int argc, const char **argv)
{
    if (argc >= 3) node (argc, argv);
    else
    {
        fprintf (stderr, "Usage: bus <NODE_NAME> <URL> <URL> ...\n");
        return 1;
    }
}

