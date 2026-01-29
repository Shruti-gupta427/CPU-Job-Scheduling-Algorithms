#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i];
    }
       float avgTAT = 0, avgWT = 0;
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (AT[i] <= currentTime && !done[i] && BT[i] < minBT) {
                minBT = BT[i];
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        CT[idx]=currentTime + BT[idx];
        TAT[idx]=CT[idx] - AT[idx];
        WT[idx]=TAT[idx] - BT[idx];
        avgWT += WT[idx];
        avgTAT += TAT[idx];


        currentTime = CT[idx];
        done[idx] = true;
        completed++;
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t"
             << AT[i] << "\t"
             << BT[i] << "\t"
             << CT[i] << "\t"
             << TAT[i] << "\t"
             << WT[i] << "\n";
    }
      cout << "Average Waiting Time = " << avgWT / n;
    cout << " Average Turnaround Time = " << avgTAT / n << endl;
   

    return 0;
}
