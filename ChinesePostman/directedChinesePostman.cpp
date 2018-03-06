/*************************************************************************
    > File Name: directedChinesePostman.cpp
    > Author: wmg_1007
    > Mail: wmg_1007@163.com
    > Created Time: 2018年03月04日 星期日 23时52分04秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int maxV = 1005;
const int INF = (1 << 30);

struct NetworkNode {
    int to, cost, cap;
    int reverseId;
    bool origin;
};

struct GraphNode {
    int to, cost;
    bool vis;
};

int numV, numE;

vector <NetworkNode> edgesNet[1005];
vector <GraphNode> edgesGraph[1005];

void AddEdgeGraph(int u, int v, int co) {
    GraphNode tmp;
    tmp.to = v, tmp.cost = co, tmp.vis = false;
    edgesGraph[u].push_back(tmp);
}

void AddEdgeNet(int u, int v, int ca, int co) {
    NetworkNode tmp;
    tmp.to = v, tmp.cost = co, tmp.cap = ca, tmp.origin = (u < numV && v < numV);
    edgesNet[u].push_back(tmp);
    tmp.to = u, tmp.cost = -co, tmp.cap = 0, tmp.origin = false;
    edgesNet[v].push_back(tmp);

    int idU = edgesNet[u].size() - 1;
    int idV = edgesNet[v].size() - 1;
    edgesNet[u][idU].reverseId = idV;
    edgesNet[v][idV].reverseId = idU;
}

int dist[maxV];
int pre[maxV], preEdgeNum[maxV];
bool vis[maxV];

// SPFA algorithm for minimum-cost flow
bool SPFA(int source, int target) {
    for (int i = 0; i < numV + 2; i++)
        dist[i] = INF, vis[i] = 0;
    dist[source] = 0;
    vis[source] = true;
    queue <int> que;
    que.push(source);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (size_t i = 0; i < edgesNet[u].size(); i++) {
            NetworkNode v = edgesNet[u][i];
            if (v.cap && dist[v.to] > dist[u] + v.cost) {
                dist[v.to] = dist[u] + v.cost;
                pre[v.to] = u;
                preEdgeNum[v.to] = i;
                if (!vis[v.to]) {
                    vis[v.to] = true;
                    que.push(v.to);
                }
            }
        }
        vis[u] = false;
    }
    return dist[target] != INF;
}

int MinimumCostFlow(int source, int target, int &maxFlow) {
    int res = 0;
    maxFlow = 0;
    while (SPFA(source, target)) {
        int flow = INF, cost = 0;
        for (int u = target; u != source; u = pre[u]) {
            flow = min(flow, edgesNet[pre[u]][preEdgeNum[u]].cap);
        }
        maxFlow += flow;
        for (int u = target; u != source; u = pre[u]) {
            edgesNet[pre[u]][preEdgeNum[u]].cap -= flow;
            int id = edgesNet[pre[u]][preEdgeNum[u]].reverseId;
            edgesNet[u][id].cap += flow;
            cost += flow * edgesNet[pre[u]][preEdgeNum[u]].cost;;
        }
        res += cost;
    }
    return res;
}

vector <int> ans;
// get euler tour
void DfsEulerTour(int u) {
    for (size_t i = 0; i < edgesGraph[u].size(); i++) {
        if (!edgesGraph[u][i].vis) {
            edgesGraph[u][i].vis = true;
            DfsEulerTour(edgesGraph[u][i].to);
        }
    }
    ans.push_back(u);
}

int deg[maxV];

int main() {
    int res = 0;
    // input the graph
    cin >> numV >> numE;
    for (int i = 0; i < numE; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        AddEdgeNet(u, v, INF, c);
        AddEdgeGraph(u, v, c);
        res += c;
        deg[u]++, deg[v]--;
    }

    // initial work
    int totDeg = 0;
    for (int i = 0; i < numV; i++) {
        if (deg[i] < 0) 
            AddEdgeNet(numV, i, -deg[i], 0);
        else if (deg[i] > 0) {
            AddEdgeNet(i, numV + 1, deg[i], 0);
            totDeg += deg[i];
        }
    }

    // minimum-cost flow
    int maxFlow = 0;
    res += MinimumCostFlow(numV, numV + 1, maxFlow);

    // cornor case & output result
    if (maxFlow == totDeg)
        cout << res << endl;
    else {
        cout << -1 << endl;
        return 0;
    }

    // add duplicate edges
    for (int u = 0; u < numV; u++)
        for (size_t i = 0; i < edgesNet[u].size(); i++) {
            if (edgesNet[u][i].origin) {
                for (int j = 0; j < INF - edgesNet[u][i].cap; j++)
                    AddEdgeGraph(u, edgesNet[u][i].to, edgesNet[u][i].cost);
            }
        }

    // output route
    DfsEulerTour(0);
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << (i > 0 ? "->" : "\n");
    return 0;
}
