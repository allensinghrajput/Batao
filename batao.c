#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_CMD 256
#define BUFFER_SIZE 512

void print_usage()
{
    printf("\n=== BATAO - Simple Ping Tool ===\n\n");
    printf("Usage:\n");
    printf("  batao <hostname/IP> [count]\n");
    printf("  batao <hostname/IP> /t\n\n");
}

int extract_time(char *line)
{
    int time = -1;
    char *ptr = strstr(line, "time=");
    if (ptr != NULL)
    {
        sscanf(ptr, "time=%d", &time);
    }
    return time;
}

int run_single_ping(char *host, int *time_ms)
{
    char command[MAX_CMD];
    char buffer[BUFFER_SIZE];

    snprintf(command, sizeof(command), "ping -n 1 %s", host);

    FILE *fp = popen(command, "r");
    if (fp == NULL)
        return 0;

    int received = 0;

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strstr(buffer, "Reply from") != NULL)
        {
            printf("%s", buffer);
            received = 1;

            int t = extract_time(buffer);
            if (t >= 0)
                *time_ms = t;
        }
    }

    pclose(fp);
    return received;
}

int main(int argc, char *argv[])
{

    char host[100];
    int continuous = 0;
    int count = 4;

    // 👉 If NO arguments → interactive mode
    if (argc < 2)
    {
        printf("=== BATAO Interactive Mode ===\n\n");

        printf("Enter Host/IP: ");
        scanf("%s", host);

        printf("Choose mode:\n");
        printf("1. Normal (fixed count)\n");
        printf("2. Continuous (/t)\n");
        printf("Enter choice (1/2): ");

        int choice;
        scanf("%d", &choice);

        if (choice == 2)
        {
            continuous = 1;
        }
        else
        {
            printf("Enter number of packets: ");
            scanf("%d", &count);
        }
    }
    else
    {
        strcpy(host, argv[1]);

        if (argc >= 3)
        {
            if (strcmp(argv[2], "/t") == 0 || strcmp(argv[2], "--t") == 0)
            {
                continuous = 1;
            }
            else
            {
                count = atoi(argv[2]);
            }
        }
    }

    printf("\nBATAO is checking %s...\n\n", host);

    int sent = 0, received = 0;
    int min = 99999, max = 0, total = 0;

    if (continuous)
    {
        printf("Continuous mode ON. Press any key to stop...\n\n");

        while (!_kbhit())
        {
            int time_ms = -1;

            sent++;
            if (run_single_ping(host, &time_ms))
            {
                received++;

                if (time_ms >= 0)
                {
                    if (time_ms < min)
                        min = time_ms;
                    if (time_ms > max)
                        max = time_ms;
                    total += time_ms;
                }
            }
        }

        _getch();
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            int time_ms = -1;

            sent++;
            if (run_single_ping(host, &time_ms))
            {
                received++;

                if (time_ms >= 0)
                {
                    if (time_ms < min)
                        min = time_ms;
                    if (time_ms > max)
                        max = time_ms;
                    total += time_ms;
                }
            }
        }
    }

    int lost = sent - received;
    float loss_percent = (sent > 0) ? ((float)lost / sent) * 100 : 0;
    int avg = (received > 0) ? total / received : 0;

    printf("\n--- BATAO Statistics ---\n");
    printf("Packets: Sent = %d, Received = %d, Lost = %d (%.0f%% loss)\n",
           sent, received, lost, loss_percent);

    if (received > 0)
    {
        printf("Minimum = %dms, Maximum = %dms, Average = %dms\n",
               min, max, avg);
    }

    printf("\nPress any key to exit...");
    _getch(); // 🔥 Keeps window open

    return 0;
}