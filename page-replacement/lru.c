#include <stdio.h>

int main() {
    int pg[100], fr[100], count[100], i, j, m, n, pf = 0, next = 1, min, hit;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the number of frames: ");
    scanf("%d", &m);
    
    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pg[i]);
    }

    // Initialize frame contents and their counters
    for (j = 0; j < m; j++) {
        fr[j] = -1;
        count[j] = 0;
    }

    printf("\nReference | Page Frames | Status\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        hit = 0;

        // Check if the page is already in a frame (HIT)
        for (j = 0; j < m; j++) {
            if (fr[j] == pg[i]) {
                hit = 1;
                count[j] = next++; // Update its recent use
                break;
            }
        }

        // If it's a MISS
        if (!hit) {
            min = 0;
            // Find the least recently used frame
            for (j = 1; j < m; j++) {
                if (count[j] < count[min]) {
                    min = j;
                }
            }
            fr[min] = pg[i];
            count[min] = next++;
            pf++;
        }

        // Print current frame status
        printf("%10d |", pg[i]);
        for (j = 0; j < m; j++) {
            if (fr[j] != -1)
                printf(" %2d", fr[j]);
            else
                printf(" --");
        }
        if (hit)
            printf("  |  HIT\n");
        else
            printf("  |  MISS\n");
    }

    printf("-------------------------------------------------\n");
    printf("Total Page Faults: %d\n", pf);

    return 0;
}
