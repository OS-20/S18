#include <stdio.h>

int main() {
    int n, i, time = 0, done = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];
    for(i = 0; i < n; i++){
        printf("P%d arrival & burst time: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    int tq;
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n|");
    while(done < n){
        int flag = 0;
        for(i = 0; i < n; i++){
            if(rt[i] > 0 && at[i] <= time){
                flag = 1;
                if(rt[i] <= tq){
                    time += rt[i];
                    printf(" P%d |", i+1);
                    rt[i] = 0;
                    ct[i] = time;
                    done++;
                } else {
                    time += tq;
                    printf(" P%d |", i+1);
                    rt[i] -= tq;
                }
            }
        }
        if(!flag) time++;
    }

    int totalTAT = 0, totalWT = 0;
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f, Average WT = %.2f\n", (float)totalTAT/n, (float)totalWT/n);
    return 0;
}
