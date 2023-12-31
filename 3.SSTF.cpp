#include <stdio.h>
#include <stdlib.h>

    int
    main()
{
    int n, head, seektime = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int sequence[n];

    printf("Enter the disk request sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &sequence[i]);
    }

    printf("Enter the initial position of the R/W head: ");
    scanf("%d", &head);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (abs(sequence[i] - head) > abs(sequence[j] - head))
            {
                int temp = sequence[i];
                sequence[i] = sequence[j];
                sequence[j] = temp;
            }
        }
    }

    printf("The Disk sequence is:\n");

    for (int i = 0; i < n; i++)
    {
        printf(" > %d", sequence[i]);
        seektime += abs(sequence[i] - head);
        head = sequence[i];
    }

    printf("\nSeek Time of SSTF = %d\n", seektime);

    return 0;
}