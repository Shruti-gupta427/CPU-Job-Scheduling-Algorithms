#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n), RT(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i];
        RT[i] = BT[i];
    }
    int q = 2;
    queue<int> rq;
    int completed = 0;
    int currenttime = AT[0];
    for (int i = 0; i < n; i++)
    {
        if (AT[i] < currenttime)
        {
            currenttime = AT[i];
        }
    }
    vector<bool> inqueue(n, false);

    // inserting those AT which are having minimum arrival time
    for (int i = 0; i < n; i++)
    {
        if (AT[i] == currenttime)
        {
            rq.push(i);
            inqueue[i] = true;
        }
    }
    float avgTAT = 0, avgWT = 0;
    while (completed < n)
    {

        // idle case handling
        if (rq.empty())
        {
            currenttime++;
            for (int i = 0; i < n; i++)
            {
                if (!inqueue[i] && AT[i] <= currenttime)
                {
                    rq.push(i);
                    inqueue[i] = true;
                }
            }
            continue;
        }
        int task = rq.front();
        rq.pop();
        int time = q > RT[task] ? RT[task] : q;
        RT[task] -= time;
        currenttime += time;
        for (int i = 0; i < n; i++)
        {
            if (!inqueue[i] && AT[i] <= currenttime)
            {
                rq.push(i);
                inqueue[i] = true;
            }
        }
        if (RT[task] > 0)
        {
            rq.push(task);
        }
        else
        {
            CT[task] = currenttime;
            TAT[task] = CT[task] - AT[task];
            WT[task] = TAT[task] - BT[task];

            avgWT += WT[task];
            avgTAT += TAT[task];
            completed++;
        }
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