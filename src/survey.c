#include <assert.h>
//#include <libc.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/survey.h>

#define SERVER "server"
#define CLIENT "client"
#define DATE   "DATE"

char *date ()
{
    time_t raw = time (&raw);
    struct tm *info = localtime (&raw);
    char *text = asctime (info);
    text[strlen(text)-1] = '\0'; // remove '\n'
    return text;
}

int server (const char *url)
{
    int sock = nn_socket (AF_SP, NN_SURVEYOR);
    assert (sock >= 0);
    assert (nn_bind (sock, url) >= 0);
    sleep(1); // wait for connections
    int sz_d = strlen(DATE) + 1; // '\0' too
    printf ("SERVER: SENDING DATE SURVEY REQUEST\n");
    int bytes = nn_send (sock, DATE, sz_d, 0);
    assert (bytes == sz_d);
    while (1)
    {
        char *buf = NULL;
        int bytes = nn_recv (sock, &buf, NN_MSG, 0);
        if (bytes == ETIMEDOUT) break;
        if (bytes >= 0)
        {
            printf ("SERVER: RECEIVED \"%s\" SURVEY RESPONSE\n", buf);
            nn_freemsg (buf);
        }
    }
    return nn_shutdown (sock, 0);
}

int client (const char *url, const char *name)
{
    int sock = nn_socket (AF_SP, NN_RESPONDENT);
    assert (sock >= 0);
    assert (nn_connect (sock, url) >= 0);
    while (1)
    {
        char *buf = NULL;
        int bytes = nn_recv (sock, &buf, NN_MSG, 0);
        if (bytes >= 0)
        {
            printf ("CLIENT (%s): RECEIVED \"%s\" SURVEY REQUEST\n", name, buf);
            nn_freemsg (buf);
            char *d = date();
            int sz_d = strlen(d) + 1; // '\0' too
            printf ("CLIENT (%s): SENDING DATE SURVEY RESPONSE\n", name);
            int bytes = nn_send (sock, d, sz_d, 0);
            assert (bytes == sz_d);
        }
    }
    return nn_shutdown (sock, 0);
}

int main (const int argc, const char **argv)
{
    if ((argc > 2) && strncmp (SERVER, argv[1], strlen (SERVER)) == 0)
        return server (argv[2]);
    else if ((argc > 3) && strncmp (CLIENT, argv[1], strlen (CLIENT)) == 0)
        return client (argv[2], argv[3]);
    else
    {
        fprintf (stderr, "Usage: survey %s|%s <URL> <ARG> ...\n",
                SERVER, CLIENT);
        return 1;
    }
}

