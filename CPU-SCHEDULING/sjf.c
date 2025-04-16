#include <stdio.h>

// Process structure
struct Process {
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int visited;// Flag to check if completed
} p[10], temp;

int main() {
    int n, i, j, min, time, total_tat = 0, total_wt = 0, count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        printf("\nEnter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].visited = 0;
    }

    // Display input table
    printf("\nPID\tAT\tBT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt);

    // Sort by arrival time initially
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    time = 0;
    while (count < n) {
        min = -1;
        for (j = 0; j < n; j++) {
            if (p[j].at <= time && p[j].visited == 0) {
                if (min == -1 || p[j].bt < p[min].bt) {
                    min = j;
                }
            }
        }

        if (min == -1) {
            time++; // No process has arrived yet
        } else {
            p[min].visited = 1;
            p[min].ct = time + p[min].bt;
            p[min].tat = p[min].ct - p[min].at;
            p[min].wt  = p[min].tat - p[min].bt;

            total_tat += p[min].tat;
            total_wt  += p[min].wt;

            time = p[min].ct;
            count++;
        }
    }

    // Final process table
    printf("\n| PID | AT  | BT  | CT  | TAT | WT  |\n");
    printf("--------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %3d | %3d | %3d | %3d | %3d |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("--------------------------------------\n");

    // Averages
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time   : %.2f\n", (float)total_wt / n);

    return 0;
}
