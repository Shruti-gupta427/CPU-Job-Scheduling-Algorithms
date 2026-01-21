#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n),RT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i];
        RT[i]=BT[i];
    }


    int completed = 0;
    int currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (AT[i] <= currentTime && !done[i] && RT[i] < minBT && RT[i]>0) {
                minBT = RT[i];
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        RT[idx]--;
        if (RT[idx] == 0) {
            CT[idx] = currentTime + 1;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];
            done[idx] = true;
            completed++;
        }
        currentTime++;
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

    return 0;
}