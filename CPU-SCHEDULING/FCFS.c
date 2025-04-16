#include <stdio.h>

// Process structure definition
struct Process {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
} p[10], temp;

int main() {
    int n, i, j;
    int time = 0;
    int total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Read process details
    for (i = 0; i < n; i++) {
        printf("\nEnter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Display initial process table
    printf("\nProcess List:\n");
    printf("PID\tAT\tBT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt);
    }

    // Sort processes by Arrival Time (simple Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // FCFS Scheduling logic
    time = 0;
    for (i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;  // CPU idle time handling
        }
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;

        time = p[i].ct;
    }

    // Display final process table
    printf("\n| PID | AT  | BT  | CT  | TAT | WT  |\n");
    printf("-------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %3d | %3d | %3d | %3d | %3d |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("-------------------------------------\n");

    // Display averages
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);

    return 0;
}
