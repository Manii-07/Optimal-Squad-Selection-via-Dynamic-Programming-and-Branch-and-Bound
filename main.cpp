#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <ctime>

using namespace std;

//PLAYER STRUCTURE
struct Player {
    string name;
    string position;
    int cost;
    int rating;
};

//MERGE SORT 
void merge(vector<Player>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Player> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].rating >= R[j].rating) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Player>& arr, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// GLOBALS
const int K = 11;

//DYNAMIC PROGRAMMING
void runDynamicProgramming(vector<Player>& players, int budget) {

    int n = players.size();

    vector<vector<vector<int>>> dp(
        n + 1,
        vector<vector<int>>(budget + 1, vector<int>(K + 1, -1))
    );

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            dp[i][w][0] = 0;
        }
    }

    clock_t start = clock();

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= budget; w++) {
            for (int c = 1; c <= K; c++) {

                dp[i][w][c] = dp[i - 1][w][c];

                if (players[i - 1].cost <= w &&
                    dp[i - 1][w - players[i - 1].cost][c - 1] != -1) {

                    dp[i][w][c] = max(
                        dp[i][w][c],
                        players[i - 1].rating +
                        dp[i - 1][w - players[i - 1].cost][c - 1]
                    );
                }
            }
        }
    }

    clock_t end = clock();

    int bestRating = dp[n][budget][K];

    if (bestRating == -1) {
        cout << "\n[DP] No valid squad found.\n";
        return;
    }

    int w = budget;
    int c = K;
    int res = bestRating;

    vector<Player> squad;

    for (int i = n; i > 0 && c > 0; i--) {

        if (dp[i][w][c] == dp[i - 1][w][c])
            continue;

        squad.push_back(players[i - 1]);

        res -= players[i - 1].rating;
        w -= players[i - 1].cost;
        c--;
    }

    mergeSort(squad, 0, squad.size() - 1);

    cout << "\n==============================\n";
    cout << "DYNAMIC PROGRAMMING RESULT\n";
    cout << "==============================\n";

    cout << "Maximum Rating: " << bestRating << "\n\n";

    int totalCost = 0;

    for (auto& p : squad) {
        cout << p.name
            << " | "
            << p.position
            << " | Cost: "
            << p.cost
            << " | Rating: "
            << p.rating
            << "\n";

        totalCost += p.cost;
    }

    cout << "\nTotal Cost: " << totalCost << " / " << budget << "\n";

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;

    cout << "Execution Time: " << timeTaken << " seconds\n";
}

//BRANCH AND BOUND
struct Node {
    int level;
    int profit;
    int cost;
    int count;
    double bound;
    vector<Player> squad;
};

bool compareRatio(Player a, Player b) {
    double r1 = (double)a.rating / a.cost;
    double r2 = (double)b.rating / b.cost;

    return r1 > r2;
}

// Upper Bound Calculation

double calculateBound(Node u, int n, int budget, vector<Player>& players) {

    if (u.cost >= budget)
        return 0;

    double bound = u.profit;
    int totalCost = u.cost;
    int j = u.level + 1;
    int totalPlayers = u.count;

    while (j < n && totalPlayers < K && totalCost + players[j].cost <= budget) {

        totalCost += players[j].cost;
        bound += players[j].rating;

        totalPlayers++;
        j++;
    }

    if (j < n && totalPlayers < K) {

        bound += (budget - totalCost) *
            ((double)players[j].rating / players[j].cost);
    }

    return bound;
}

void runBranchAndBound(vector<Player> players, int budget) {

    sort(players.begin(), players.end(), compareRatio);

    int n = players.size();

    queue<Node> Q;

    Node u, v;

    v.level = -1;
    v.profit = 0;
    v.cost = 0;
    v.count = 0;
    v.bound = 0;

    Q.push(v);

    int maxProfit = 0;

    vector<Player> bestSquad;

    clock_t start = clock();

    while (!Q.empty()) {

        v = Q.front();
        Q.pop();

        if (v.level == n - 1)
            continue;

        u.level = v.level + 1;

        // INCLUDE PLAYER
        u.cost = v.cost + players[u.level].cost;
        u.profit = v.profit + players[u.level].rating;
        u.count = v.count + 1;

        u.squad = v.squad;
        u.squad.push_back(players[u.level]);

        if (u.cost <= budget && u.count == K && u.profit > maxProfit) {
            maxProfit = u.profit;
            bestSquad = u.squad;
        }

        u.bound = calculateBound(u, n, budget, players);

        if (u.bound > maxProfit && u.count <= K)
            Q.push(u);

        // EXCLUDE PLAYER
        u.cost = v.cost;
        u.profit = v.profit;
        u.count = v.count;
        u.squad = v.squad;

        u.bound = calculateBound(u, n, budget, players);

        if (u.bound > maxProfit)
            Q.push(u);
    }

    clock_t end = clock();

    mergeSort(bestSquad, 0, bestSquad.size() - 1);

    cout << "\n==============================\n";
    cout << "BRANCH AND BOUND RESULT\n";
    cout << "==============================\n";

    cout << "Maximum Rating: " << maxProfit << "\n\n";

    int totalCost = 0;

    for (auto& p : bestSquad) {

        cout << p.name
            << " | "
            << p.position
            << " | Cost: "
            << p.cost
            << " | Rating: "
            << p.rating
            << "\n";

        totalCost += p.cost;
    }

    cout << "\nTotal Cost: " << totalCost << " / " << budget << "\n";

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;

    cout << "Execution Time: " << timeTaken << " seconds\n";
}

// ---------------- MAIN ----------------
int main() {

    vector<Player> players;

    ifstream file("players.csv");

    string line, word;

    if (file.is_open()) {

        getline(file, line);

        while (getline(file, line)) {

            stringstream s(line);

            Player p;

            getline(s, p.name, ',');
            getline(s, p.position, ',');

            getline(s, word, ',');
            p.cost = stoi(word);

            getline(s, word, ',');
            p.rating = stoi(word);

            players.push_back(p);
        }

        file.close();

    }
    else {

        cout << "Error opening players.csv\n";
        return 1;
    }

    int budget;

    cout << "Enter Budget: ";
    cin >> budget;

    // RUN BOTH ALGORITHMS

    runDynamicProgramming(players, budget);

    runBranchAndBound(players, budget);

    return 0;
}
