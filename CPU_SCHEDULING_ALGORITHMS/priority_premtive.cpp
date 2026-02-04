#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> pid(n), AT(n), BT(n), CT(n), TAT(n), WT(n), PR(n), RT(n);
    float avgTAT = 0, avgWT = 0;

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT BT PR for P" << pid[i] << ": ";
        cin >> AT[i] >> BT[i] >> PR[i];
        RT[i] = BT[i];
    }

    int completed = 0, currenttime = 0;
    vector<bool> done(n, false);

    vector<tuple<int, int, int>> gantt;

    int prev = -2;   
    int startTime = 0;

    while (completed < n)
    {
        int idx = -1;
        int minPR = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (AT[i] <= currenttime && !done[i])
            {
                if (PR[i] < minPR) 
                {
                    minPR = PR[i];
                    idx = i;
                }
            }
        }

       
        if (idx == -1)
        {
            if (prev != -1)
            {
                if (prev != -2)
                    gantt.push_back({prev, startTime, currenttime});

                startTime = currenttime;
                prev = -1;
            }
            currenttime++;
            continue;
        }

        
        if (prev != idx)
        {
            if (prev != -2)
                gantt.push_back({prev, startTime, currenttime});

            startTime = currenttime;
            prev = idx;
        }

        RT[idx]--;
        currenttime++;

        if (RT[idx] == 0)
        {
            CT[idx] = currenttime;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];

            avgWT += WT[idx];
            avgTAT += TAT[idx];

            done[idx] = true;
            completed++;
        }
    }

 
    gantt.push_back({prev, startTime, currenttime});

   
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
             << PR[i] << "\t" << CT[i] << "\t"
             << TAT[i] << "\t" << WT[i] << "\n";
    }

    cout << "\nGantt Chart:\n";
    for (auto &g : gantt)
    {
        int p, s, e;
        tie(p, s, e) = g;
        if (p == -1)
            cout << "| IDLE ";
        else
            cout << "| P" << pid[p] << " ";
    }
    cout << "|\n";

    for (auto &g : gantt)
    {
        int p, s, e;
        tie(p, s, e) = g;
        cout << s << "     ";
    }
    cout << currenttime << "\n";

    cout << "\nAverage Waiting Time = " << avgWT / n;
    cout << "\nAverage Turnaround Time = " << avgTAT / n << endl;

    return 0;
}
