#include <stdio.h>

struct frame {
    int content;
    int frequency;
    int count;
};

int main() {
    int i, j, pg[20], pf = 0, n, m, hit, k = 0, min;
    struct frame fr[20];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &m);

    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pg[i]);
    }

    // Initialize frames
    for (j = 0; j < m; j++) {
        fr[j].content = -1;
        fr[j].frequency = 0;
        fr[j].count = 0;
    }

    printf("\nReference | Frames ");
    printf("| Status\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        hit = 0;

        // Check for page hit
        for (j = 0; j < m; j++) {
            if (pg[i] == fr[j].content) {
                fr[j].frequency++;
                fr[j].count = i;
                hit = 1;
                break;
            }
        }

        // If MISS
        if (!hit) {
            if (k < m) {  // If there’s empty space
                fr[k].content = pg[i];
                fr[k].frequency = 1;
                fr[k].count = i;
                k++;
                pf++;
            } else { // Replace using LFU logic
                min = 0;
                for (j = 1; j < m; j++) {
                    if (fr[j].frequency < fr[min].frequency ||
                        (fr[j].frequency == fr[min].frequency && fr[j].count < fr[min].count)) {
                        min = j;
                    }
                }
                fr[min].content = pg[i];
                fr[min].frequency = 1;
                fr[min].count = i;
                pf++;
            }
        }

        // Print current frame state
        printf("%10d |", pg[i]);
        for (j = 0; j < m; j++) {
            if (fr[j].content != -1)
                printf(" %2d", fr[j].content);
            else
                printf(" --");
        }
        if (hit)
            printf("  |  HIT\n");
        else
            printf("  |  MISS\n");
    }

    printf("--------------------------------------------------\n");
    printf("Total Page Faults: %d\n", pf);

    return 0;
}
