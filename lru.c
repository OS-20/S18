#include <stdio.h>

int main() {
    int n, f, i, j, k;
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);
    int ref[n];
    printf("Enter reference string: ");
    for(i = 0; i < n; i++) scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], time[f];
    for(i = 0; i < f; i++) frames[i] = -1;

    int page_faults = 0;

    printf("\nPage replacement sequence:\n");
    for(i = 0; i < n; i++){
        int found = 0;
        for(j = 0; j < f; j++){
            if(frames[j] == ref[i]){
                time[j] = i;
                found = 1;
                break;
            }
        }

        if(!found){
            page_faults++;
            int idx = -1, lru = n+1;
            for(j = 0; j < f; j++){
                if(frames[j] == -1){
                    idx = j;
                    break;
                }
            }

            if(idx == -1){
                for(j = 0; j < f; j++){
                    if(time[j] < lru){
                        lru = time[j];
                        idx = j;
                    }
                }
            }

            frames[idx] = ref[i];
            time[idx] = i;
        }

        for(j = 0; j < f; j++){
            if(frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        if(!found) printf("-> Page Fault");
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}
