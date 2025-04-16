#include <stdio.h>

int instance[20];
int max[50][50];
int available[50][50];
int avail[50];
int allocation[50][50];
int need[50][50];
int ans[50];
int visited[50];

int main()
{
    int z = 0, n, m, i, j, k, alloc = 0, flag = 0, y, p = 0;

    // Input the number of instances
    printf("Enter the number of instances: ");
    scanf("%d", &m);

    // Input the instances available
    printf("Enter the instances: ");
    for (i = 0; i < m; i++)
    {
        printf("%c : ", (i + 65));
        scanf("%d", &instance[i]);
    }

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the max matrix
    printf("Enter the max matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("p%d[%c] : ", i + 1, (j + 65));
            scanf("%d", &max[i][j]);
        }
    }

    // Input the allocation matrix
    printf("Enter the allocation matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("p%d[%c] : ", i + 1, (j + 65));
            scanf("%d", &allocation[i][j]);
            visited[i] = 0;  // initialize visited array
        }
    }

    // Calculate the need matrix and available resources
    for (j = 0; j < m; j++)
    {
        alloc = 0;
        for (i = 0; i < n; i++)
        {
            // Calculate the need matrix
            need[i][j] = max[i][j] - allocation[i][j];
            alloc += allocation[i][j];
        }
        // Calculate the available resources
        avail[j] = instance[j] - alloc;
    }

    // Copy available resources to the available matrix
    for (j = 0; j < m; j++)
    {
        available[0][j] = avail[j];
    }

    // Banker's Algorithm - Safe Sequence Check
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                flag = 0;
                for (j = 0; j < m; j++)
                {
                    // Check if the need of the i-th process is greater than available resources
                    if (need[i][j] > available[z][j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    visited[i] = 1;
                    ans[p] = i;
                    p++;
                    // Update the available resources after the process is completed
                    for (y = 0; y < m; y++)
                    {
                        available[z + 1][y] = available[z][y] + allocation[i][y];
                    }
                    z++;
                }
            }
        }
    }

    // Check if all processes are visited (safe sequence found)
    int safe = 1;
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            safe = 0;
            printf("The following system is not safe \n");
            break;
        }
    }

    // Output the safe sequence if the system is safe
    if (safe == 1)
    {
        printf("The following system is safe \n");
        printf("Max        |   Allocation |   Need    |    Available   | \n");

        // Display max, allocation, need, and available matrices
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                printf("%2d ", max[i][j]);
            }
            printf("    |");
            for (j = 0; j < m; j++)
            {
                printf("%2d ", allocation[i][j]);
            }
            printf("    |");
            for (j = 0; j < m; j++)
            {
                printf("%2d ", need[i][j]);
            }
            printf("    |");
            for (j = 0; j < m; j++)
            {
                printf("%2d ", available[i][j]);
            }
            printf("    |");
            printf("\n");
        }

        // Print the safe sequence
        for (i = 0; i < n; i++)
        {
            printf("p%d>>>", ans[i]);
        }
        printf("\n\n");

        // Display available resources after execution
        printf("Available after execution : ");
        for (j = 0; j < m; j++)
        {
            printf("%2d ", available[z][j]);
        }
    }

    return 0;
}
