#include <assert.h>
//#include <libc.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#define NODE0 "node0"
#define NODE1 "node1"
#define DATE "DATE"

char *date ()
{
    time_t raw = time (&raw);
    struct tm *info = localtime (&raw);
    char *text = asctime (info);
    text[strlen(text)-1] = '\0'; // remove '\n'
    return text;
}

int node0 (const char *url)
{
    int sz_date = strlen (DATE) + 1; // '\0' too
    int sock = nn_socket (AF_SP, NN_REP);
    assert (sock >= 0);
    assert (nn_bind (sock, url) >= 0);
    while (1)
    {
        char *buf = NULL;
        int bytes = nn_recv (sock, &buf, NN_MSG, 0);
        assert (bytes >= 0);
        if (strncmp (DATE, buf, sz_date) == 0)
        {
            printf ("NODE0: RECEIVED DATE REQUEST\n");
            char *d = date();
            int sz_d = strlen(d) + 1; // '\0' too
            printf ("NODE0: SENDING DATE %s\n", d);
            bytes = nn_send (sock, d, sz_d, 0);
            assert (bytes == sz_d);
        }
        nn_freemsg (buf);
    }
    return nn_shutdown (sock, 0);
}

int node1 (const char *url)
{
    int sz_date = strlen(DATE) + 1; // '\0' too
    char *buf = NULL;
    int bytes = -1;
    int sock = nn_socket (AF_SP, NN_REQ);
    assert (sock >= 0);
    assert (nn_connect (sock, url) >= 0);
    printf ("NODE1: SENDING DATE REQUEST %s\n", DATE);
    bytes = nn_send (sock, DATE, sz_date, 0);
    assert (bytes == sz_date);
    bytes = nn_recv (sock, &buf, NN_MSG, 0);
    assert (bytes >= 0);
    printf ("NODE1: RECEIVED DATE %*s\n", bytes, buf);
    nn_freemsg (buf);
    return nn_shutdown (sock, 0);
}

int main (const int argc, const char **argv)
{
    if ((argc > 2) && strncmp (NODE0, argv[1], strlen (NODE0)) == 0)
        return node0 (argv[2]);
    else if ((argc > 2) && strncmp (NODE1, argv[1], strlen (NODE1)) == 0)
        return node1 (argv[2]);
    else
    {
        fprintf (stderr, "Usage: reqrep %s|%s <URL> <ARG> ...\n",
                NODE0, NODE1);
        return 1;
    }
}

