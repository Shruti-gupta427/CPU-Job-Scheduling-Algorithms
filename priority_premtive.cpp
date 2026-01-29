#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n), PR(n), RT(n);

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Arrival Time Burst Time and Priority P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i] >> PR[i];
        RT[i] = BT[i];
    }
    int completed = 0;
    int currenttime = 0;
    vector<bool> done(n, false);
    while (completed < n)
    {
        int idx = -1;
        int maxPR = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            if (AT[i] <= currenttime && PR[i] > maxPR && !done[i])
            {
                maxPR = PR[i];
                idx = i;
            }
        }

        if (idx == -1)
        {
            currenttime++;
            continue;
        }
        RT[idx]--;
        currenttime++;

        if (RT[idx] == 0)
        {
            CT[idx] = currenttime;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];

            done[idx] = true;

            completed++;
        }
    }
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t"
             << AT[i] << "\t"
             << BT[i] << "\t"
             << PR[i] << "\t"
             << CT[i] << "\t"
             << TAT[i] << "\t"
             << WT[i] << "\n";
    }
    return 0;
}
