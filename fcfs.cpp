#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (AT[j] > AT[j + 1]) {
                swap(AT[j], AT[j + 1]);
                swap(BT[j], BT[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    CT[0] = AT[0] + BT[0];
    for (int i = 1; i < n; i++) {
        CT[i] = max(CT[i - 1], AT[i]) + BT[i];
    }
    int totaltat=0;
    int totalwt=0;
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        totaltat+=TAT[i];
        WT[i] = TAT[i] - BT[i];
        totalwt+=WT[i];
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
double avgTAT=totaltat/n;
double avgwt=totalwt/n;
cout<<"AvgTAT = "<<avgTAT<<"AvgWT = "<<avgwt;
    return 0;
}
