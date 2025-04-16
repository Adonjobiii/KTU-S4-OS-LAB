#include <stdio.h>

// Process structure definition
struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int visited;    // Flag to check if added to queue
    int remaining;  // Remaining Burst Time
} p[10];

// Queue implementation
int front = -1, rear = -1, q[100];

void push(int x) {
    if (front == -1) front = 0;
    q[++rear] = x;
}

int pop() {
    if (front == -1 || front > rear)
        return -1;
    int elem = q[front++];
    if (front > rear)
        front = rear = -1;
    return elem;
}

int main() {
    int n, i, time = 0, total_tat = 0, total_wt = 0, count = 0;
    int quantum, elem, k, idle_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++) {
        printf("\nEnter Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].visited = 0;
        p[i].remaining = p[i].bt;
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &quantum);

    // Display initial process info
    printf("\nPID\tAT\tBT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt);

    printf("\nGantt Chart:\n");

    while (count < n) {
        // Push arrived processes into the queue
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].visited == 0) {
                push(i);
                p[i].visited = 1;
            }
        }

        elem = pop();

        if (elem == -1) {
            time++;
            idle_time++;
        } else {
            if (idle_time != 0) {
                printf("%d >>>>>>>>>>>>> %d Idle\n", time - idle_time, time);
                idle_time = 0;
            }
            printf("%d >>>>>>>>>>>>> ", time);

            // Execute process for time quantum or until completion
            k = 0;
            while (k < quantum && p[elem].remaining > 0) {
                p[elem].remaining--;
                time++;
                k++;

                // Check for newly arrived processes during execution
                for (i = 0; i < n; i++) {
                    if (p[i].at <= time && p[i].visited == 0) {
                        push(i);
                        p[i].visited = 1;
                    }
                }
            }

            if (p[elem].remaining == 0) {
                printf("%d P%d (Complete)\n", time, p[elem].pid);
                p[elem].ct = time;
                p[elem].tat = p[elem].ct - p[elem].at;
                p[elem].wt = p[elem].tat - p[elem].bt;

                total_tat += p[elem].tat;
                total_wt += p[elem].wt;
                count++;
            } else {
                printf("%d P%d\n", time, p[elem].pid);
                push(elem);  // Put back in queue
            }
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
