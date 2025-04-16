#include <stdio.h>

// Process structure definition
struct Process {
    int pid;       // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int priority;  // Priority (lower value = higher priority)
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int visited;   // Whether the process has been scheduled
} p[10], temp;

int main() {
    int n, i, j;
    int time = 0, count = 0;
    int selected;
    int total_tat = 0, total_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        printf("\nEnter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        printf("Enter Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
        p[i].visited = 0;
    }

    // Display initial process table
    printf("\nProcess List:\n");
    printf("PID\tAT\tBT\tPriority\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority);
    }

    // Priority Scheduling logic
    while (count < n) {
        selected = -1;
        for (j = 0; j < n; j++) {
            if (p[j].at <= time && p[j].visited == 0) {
                if (selected == -1 || p[j].priority < p[selected].priority) {
                    selected = j;
                }
            }
        }

        if (selected == -1) {
            // If no process has arrived yet
            time++;
        } else {
            p[selected].visited = 1;
            p[selected].ct = time + p[selected].bt;
            p[selected].tat = p[selected].ct - p[selected].at;
            p[selected].wt = p[selected].tat - p[selected].bt;

            total_tat += p[selected].tat;
            total_wt += p[selected].wt;

            time = p[selected].ct;
            count++;
        }
    }

    // Display final process table
    printf("\n| PID | AT  | BT  | PRI | CT  | TAT | WT  |\n");
    printf("------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %3d | %3d | %3d | %3d | %3d | %3d |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("------------------------------------------------\n");

    // Display averages
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);

    return 0;
}
