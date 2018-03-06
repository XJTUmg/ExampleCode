/*************************************************************************
    > File Name: undirectedChinesePostman.cpp
    > Author: wmg_1007
    > Mail: wmg_1007@163.com
    > Created Time: 2018年03月06日 星期二 22时32分25秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int maxV = 105;
const int maxE = maxV * maxV;
const int maxOdd = 21;
const int INF = (1 << 30);

struct GraphNode {
    int to, cost;
    bool vis;
};

int numV, numE;

vector <GraphNode> edgesGraph[maxV];
int reverseId[maxV][maxE];

void AddEdgeGraph(int u, int v, int co) {
    GraphNode tmp;
    tmp.to = v, tmp.cost = co, tmp.vis = false;
    edgesGraph[u].push_back(tmp);
    tmp.to = u, tmp.cost = co, tmp.vis = false;
    edgesGraph[v].push_back(tmp);

    int idU = edgesGraph[u].size() - 1;
    int idV = edgesGraph[v].size() - 1;
    reverseId[u][idU] = idV;
    reverseId[v][idV] = idU;
}

int dist[maxV][maxV];
int pre[maxV][maxV], preEdgeNum[maxV][maxV];

// Dijkstra algorithm
bool Dijkstra(int source) {
    dist[source][source] = 0;
    for (int i = 0; i < numV; i++)
        dist[source][i] = (i == source ? 0 : INF);

    bool vis[maxV];
    memset(vis, false, sizeof(vis));
    while (1) {
        int p = -1, distP = INF;
        for (int i = 0; i < numV; i++)
            if (!vis[i] && dist[source][i] < distP)
                p = i, distP = dist[source][i];
        if (p == -1)
            break;
        vis[p] = true;
        for (size_t i = 0; i < edgesGraph[p].size(); i++) {
            int v = edgesGraph[p][i].to;
            if (dist[source][v] > dist[source][p] + edgesGraph[p][i].cost) {
                dist[source][v] = dist[source][p] + edgesGraph[p][i].cost;
                pre[source][v] = p;
                preEdgeNum[source][v] = i;
            }
        }
    }
    for (int i = 0; i < numV; i++)
        if (dist[source][i] == INF)
            return false;
    return true;
}

int deg[maxV];
vector <int> oddVertex;

int dp[(1 << maxOdd) + 5];
pair<int, int> preDp[(1 << maxOdd) + 5];

// add duplicate edge to graph
void changeGraph(pair<int, int> p) {
    int u = oddVertex[p.first];
    int v = oddVertex[p.second];
    while (v != u) {
        AddEdgeGraph(pre[u][v], v, edgesGraph[pre[u][v]][preEdgeNum[u][v]].cost);
        v = pre[u][v];
    }
}

vector <int> ans;
// get euler tour
void DfsEulerTour(int u) {
    for (size_t i = 0; i < edgesGraph[u].size(); i++) {
        if (!edgesGraph[u][i].vis) {
            edgesGraph[u][i].vis = true;
            int v = edgesGraph[u][i].to;
            edgesGraph[v][reverseId[u][i]].vis = true;
            DfsEulerTour(v);
        }
    }
    ans.push_back(u);
}

int main() {
    int res = 0;
    // input the graph
    cin >> numV >> numE;
    for (int i = 0; i < numE; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        AddEdgeGraph(u, v, c);
        res += c;
        deg[u]++, deg[v]++;
    }

    // initial work
    bool connected = true;
    for (int i = 0; i < numV; i++) {
        if (deg[i] & 1) {
            oddVertex.push_back(i);
            connected &= Dijkstra(i);
        }
    }

    // cornor case
    if (!connected) {
        cout << -1 << endl;
        return 0;
    }

    // Dynamic programming
    int totOdd = oddVertex.size();
    for (int S = 1; S < (1 << totOdd); S++) {
        int totOne = 0;
        for (int i = 0; i < totOdd; i++)
            if (S & (1 << i))
                totOne++;
        if (totOne & 1)
            continue;
        dp[S] = INF;
        for (int i = 0; i < totOdd; i++)
            for (int j = 0; j < totOdd; j++) {
                if (i == j)
                    continue;
                if ((S & (1 << i)) && (S & (1 << j))) {
                    int tmp = dp[S - (1 << i) - (1 << j)] + dist[oddVertex[i]][oddVertex[j]];
                    if (tmp < dp[S]) {
                        preDp[S] = make_pair(i, j);
                        dp[S] = tmp;
                    }
                }
            }
    }

    // output result
    res += dp[(1 << totOdd) - 1];
    cout << res << endl;

    // change graph
    int state = (1 << totOdd) - 1;
    while (state) {
        changeGraph(preDp[state]);
        state -= (1 << preDp[state].first) + (1 << preDp[state].second);
    }

    // output route
    DfsEulerTour(0);
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << (i > 0 ? "---" : "\n");
    return 0;
}
