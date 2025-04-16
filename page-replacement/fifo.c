#include <stdio.h>

int main() {
    int pg[100], fr[100], i, j, k = 0, m, n, found, page_faults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &m);

    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pg[i]);
    }

    // Initialize frame slots to -1 (empty)
    for (j = 0; j < m; j++) {
        fr[j] = -1;
    }

    printf("\n Reference | Page Frames ");
    printf("| Status\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if the page is already in one of the frames
        for (j = 0; j < m; j++) {
            if (pg[i] == fr[j]) {
                found = 1;
                break;
            }
        }

        printf("%10d |", pg[i]);

        if (!found) {
            // Page fault: replace page in the current frame (FIFO)
            fr[k] = pg[i];
            k = (k + 1) % m;
            page_faults++;
        }

        // Print current state of frames
        for (j = 0; j < m; j++) {
            if (fr[j] != -1)
                printf(" %2d", fr[j]);
            else
                printf(" --");
        }

        if (found)
            printf("  |  HIT\n");
        else
            printf("  |  MISS\n");
    }

    printf("--------------------------------------------------\n");
    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
