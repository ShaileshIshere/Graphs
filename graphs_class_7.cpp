#include<bits/stdc++.h>

using namespace std;

class Graph{
    unordered_map<char, list<pair<char, int> > > adjList;
    unordered_map<int, list<pair<int, int> > > adjList;
    unordered_map<int, list<int> > adjList;

    // printing graphs with weights in it
    void print() {
        for(auto i : adjList) {
            cout << i.first << " -> [ ";
            for(auto j : i.second)
                cout << "[ " << j.first << ", " << j.second << " ]";
            cout << " ]" << endl;
        }
    }

    // printing graphs without weights in it
    void print() {
        for(auto i : adjList) {
            cout << i.first << " -> [ ";
            for(auto j : i.second)
                cout << "[ " << j << " ]";
            cout << " ]" << endl;
        }
    }

    void bellman_ford(int n, char src) {
        // initial state
        vector<int> dist(n, INT_MAX);
        dist[src-'a'] = 0;

        // now we've to run (N-1) times RELAXATION
        for(int i=0; i<n; ++i) {
            // traverse on entire edge list
            for(auto a : adjList) {
                char u = a.first;
                for(auto b : a.second) {
                    char v = b.first;
                    int wt = b.second;
                    if(dist[u-'a'] + wt < dist[v-'a'] && dist[u-'a'] != INT_MAX)
                        dist[v-'a'] = dist[u-'a'] + wt;
                }
            }
        }

        /*here we can say that shortest distance between all nodes is ready
        now we gotta check for (-ve) cycle
        1st time RELAXATION begins*/
        bool flag = false;
        for(auto a : adjList) {
            char u = a.first;
            for(auto b : a.second) {
                char v = b.first;
                int wt = b.second;
                if(dist[u-'a'] + wt < dist[v-'a'] && dist[u-'a'] != INT_MAX) {
                    flag = true;
                    break;
                    dist[v-'a'] = dist[u-'a'] + wt;
                }
            }
        }

        if(flag)
            cout << "(-ve) cycle present" << endl;
        else {
            cout << "there isn't any (-ve) cycle here" << endl;
            cout << "here is the shortest distance of each node : " << "[ ";
            for(auto x : dist)
                cout << x << " ";
            cout << "]" << endl;
        }
    }

    void floyd_warshall(int n) {
        vector<vector<int>> dist(n, vector<int>(n, 1e9));

        // place [0] at diagonal
        for(int i=0; i<n; ++i)
            dist[i][i] = 0;

        // update dist array according to the given weights in graph
        for(auto a : adjList) {
            char u = a.first;
            for(auto b : a.second) {
                char v = b.first;
                int wt = b.second;
                dist[u][v] = wt;
            }
        }

        // main => helper logic
        for(int helper=0; helper<n; ++helper) {
            for(int src=0; src<n; ++src) {
                for(int dest=0; dest<n; ++dest)
                    dist[src][dest] = min(dist[src][dest], dist[src][helper] + dist[helper][dest]);
            }
        }

        // print the dist array
        for(int i=0; i<n; ++i) {
            cout << i << " => " << "[ ";
            for(int j=0; j<n; ++j) 
                cout << dist[i][j] << " ";
            cout << "]" << endl;
        }
    }

    void dfs_I(int src, stack<int> &st, unordered_map<int, bool> &vis_I) {
        vis_I[src] = 1;
        for(auto nbr : adjList[src]) {
            if(!vis_I[nbr])
                dfs_I(nbr, st, vis_I);
        }
        st.push(src);
    }
    void dfs_II(int src, unordered_map<int, bool> &vis_II, unordered_map<int, list<int> > &new_adjList) {
        vis_II[src] = 1;
        cout << src << " -> ";
        for(auto nbr : new_adjList[src]) {
            if(!vis_II[nbr])
                dfs_II(nbr, vis_II, new_adjList);
        }
    }
    int kosa_raju(int n) {
        // step 1: get the ordering
        stack<int> ordering;
        unordered_map<int, bool> vis_I;
        for(int i=0; i<n; ++i) {
            if(!vis_I[i])
                dfs_I(i, ordering, vis_I);
        }

        // step 2: reverse the edges
        unordered_map<int, list<int> > new_adjList;
        for(auto a : adjList) {
            for(auto b : a.second) {
                int u = a.first;
                int v = b;
                new_adjList[v].push_back(u);
            }
        }

        // step 3: traverse using ordering and count components
        int count = 0;
        unordered_map<int, bool> vis_II;
        while(!ordering.empty()) {
            int nbr = ordering.top(); ordering.pop();
            if(!vis_II[nbr]) {
                cout << "this is " << count+1 << " SCC : ";
                dfs_II(nbr, vis_II, new_adjList);
                cout << endl; 
                count++;
            }
        }
        return count;
    }
public:
    // for char type graphs
    void addEdge(char u, char v, int w, bool direction) {
        if(direction)
            adjList[u].push_back({v, w});
        else {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
    }

    // for int type graphs
    void addEdge(int u, int v, int w, bool direction) {
        if(direction)
            adjList[u].push_back({v, w});
        else {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
    }

    // for graphs that doesn't require weights
    void addEdge(int u, int v, bool direction) {
        if(direction) 
            adjList[u].push_back(v);
        else {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    void print_graph() {
        return print();
    }
    void get_algo_I(int n, int src) {
        return bellman_ford(n, src);
    }
    void get_algo_II(int n) {
        return floyd_warshall(n);
    }
    int get_algo_III(int n) {
        return kosa_raju(n);
    }
};

// Critical Connections in a Network - LC(1192)
class Solution {
    void solve(int src, int parent, unordered_map<int, list<int> > &adj, int &timer, 
    vector<vector<int>> &ans, vector<int> &tin, vector<int> &low, unordered_map<int, bool> &vis) {
        vis[src] = 1;
        tin[src] = timer;
        low[src] = timer;
        timer++;

        for(auto nbr : adj[src]) {
            if(nbr == parent)
                continue;
            else if(!vis[nbr]) {
                // step 1:
                solve(nbr, src, adj, timer, ans, tin, low, vis);
                // step 2: low update 
                low[src] = min(low[src], low[nbr]);
                // step 3: bridge testing
                if(low[nbr] > tin[src]) {
                    vector<int> temp;
                    temp.push_back(src);
                    temp.push_back(nbr);
                    ans.push_back(temp);
                }
            }
            else {
                // a new edge founded, we gotta update [low]
                low[src] = min(low[src], low[nbr]);
                // no need of bridge testing
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        unordered_map<int, list<int> > adj;
        for(auto i:connections) {
            int u = i[0];
            int v = i[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int timer = 1, src = 0, parent = -1;
        vector<vector<int>> ans;
        vector<int> low(n, 0);
        vector<int> tin(n, 0);
        unordered_map<int, bool> vis;
        solve(src, parent, adj, timer, ans, tin, low, vis);
        return ans;
    }
};

int main() {

    Graph g;
    int n, w, direction, nodes;
    char u, v;
    cout << "enter no. of edges : ";
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter [u], [v], [w] or [direction] : ";
        cin >> u >> v >> w >> direction;
        g.addEdge(u, v, w, direction);
    }
    g.print_graph();
    char src;
    cout << "enter [src] and [nodes] : ";
    cin >> src >> nodes;
    g.get_algo_I(nodes, src);

    int n, u, v, w, direction, nodes;
    cout << "enter no. of edges : ";
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter [u], [v], [w] or [direction] : ";
        cin >> u >> v >> w >> direction;
        g.addEdge(u, v, w, direction);
    }
    g.print_graph();
    g.get_algo_II(4);

    int n, u, v, direction;
    cout << "enter no. of edges : ";
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter [u], [v] or [direction] : ";
        cin >> u >> v >> direction;
        g.addEdge(u, v, direction);
    }
    g.print_graph();
    cout << "no. of SCC : " << g.get_algo_III(8) << endl;

    Solution s;
    int n, nodes;
    cout << "enter [n] and no. of nodes : ";
    cin >> n >> nodes;
    vector<vector<int>> connections(n, vector<int>(2));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<2; ++j)
            cin >> connections[i][j];
    } 
    vector<vector<int>> results = s.criticalConnections(nodes, connections);
    for(auto row : results) {
        cout << "[ ";
        for(auto col : row)
            cout << col << " ";
        cout << "]" << endl;
    }
     
    return 0;
}