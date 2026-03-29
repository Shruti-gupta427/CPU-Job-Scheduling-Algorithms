#include <iostream>
#include <vector>
using namespace std;
bool isSafe(int n, int m,
            vector<vector<int>> &allocation,
            vector<vector<int>> &need,
            vector<int> &available,
            vector<int> &safeSequence) {

    vector<int> work = available;
    vector<bool> finish(n, false);
    safeSequence.clear();

    bool changed = true;

    while (changed) {
        changed = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {

                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    safeSequence.push_back(i);
                    changed = true;
                }
            }
        }
    }

    
    for (int i = 0; i < n; i++)
        if (!finish[i])
            return false;

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maxm(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];
  
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxm[i][j];

    for (int j = 0; j < m; j++)
        cin >> available[j];

    cout << "Need Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxm[i][j] - allocation[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> safeSequence;
    if (isSafe(n, m, allocation, need, available, safeSequence)) {
        cout << "SAFE\nSafe Sequence: ";
        for (int i : safeSequence)
            cout << "P" << i << " ";
        cout << endl;
    } else {
        cout << "UNSAFE\n";
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int pid;
        cin >> pid;

        vector<int> request(m);
        for (int j = 0; j < m; j++)
            cin >> request[j];

        bool valid = true;

        for (int j = 0; j < m; j++)
            if (request[j] > need[pid][j])
                valid = false;

    
        for (int j = 0; j < m; j++)
            if (request[j] > available[j])
                valid = false;

        if (!valid) {
            cout << "DENIED\n";
            continue;
        }

    
        for (int j = 0; j < m; j++) {
            available[j] -= request[j];
            allocation[pid][j] += request[j];
            need[pid][j] -= request[j];
        }

      
        if (isSafe(n, m, allocation, need, available, safeSequence)) {
            cout << "GRANTED\n";
        } else {
            cout << "DENIED\n";

            for (int j = 0; j < m; j++) {
                available[j] += request[j];
                allocation[pid][j] -= request[j];
                need[pid][j] += request[j];
            }
        }
    }
    return 0;
}