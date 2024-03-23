#include<bits/stdc++.h>

using namespace std;

class Graph{
private:
    bool vis;
    unordered_map<int, list<int>> adjList;

    void print_graph() {
        for(auto  i : adjList) {
            cout << i.first << " -> [ ";
            for(auto j : i.second)
                cout << j << " ";
            cout << "]" << endl;
        }
    }

    void topological_sort_DFS(int src, map<int, int> &vis, stack<int> &st) {
        vis[src] = true;

        for(auto nbr : adjList[src]) {
            if(!vis[nbr])
                topological_sort_DFS(nbr, vis, st);
        }

        st.push(src);
    }

    void topological_sort_BFS(int n, vector<int> &order) {
        queue<int> q;
        unordered_map<int, int> indegree;

        // initialize all nodes with their indegree
        for(auto i : adjList) {
            for(auto j : i.second)
                indegree[j]++;
        }

        // push those nodes in queue which has [0] indegrees
        for(int node=0; node<n; ++node) {
            if(indegree[node] == 0)
                q.push(node);
        }

        // BFS
        while(!q.empty()) {
            int front_node = q.front(); q.pop();
            // cout << front_node << " ";
            order.push_back(front_node);

            /*reduce the indegree of its neighbors by one 
            and check if they can be added to queue*/
            for(auto nbr : adjList[front_node]) {
                indegree[nbr]--;
                if(indegree[nbr] == 0)
                    q.push(nbr);
            }
        }
    }

    void shortest_path_BFS(int src, int dest) {
        queue<int> q;
        unordered_map<int, bool> visited;
        unordered_map<int, int> parent;

        // initial state
        q.push(src);
        visited[src] = 1;
        parent[src] = -1;

        while(!q.empty()) {
            int front = q.front(); q.pop();
            for(auto nbr : adjList[front]) {
                if(!visited[nbr]) {
                    q.push(nbr);
                    parent[nbr] = front;
                    visited[nbr] = 1;
                }
            }
        }

        // creating the array that stores the shortest path
        vector<int> ans;
        while(dest != -1) {
            ans.push_back(dest);
            dest = parent[dest];
        }
        reverse(ans.begin(), ans.end());

        // print the shortest path from source to destination
        cout << "Shortest Path: ";
        for(auto i : ans)
            cout << i << " -> ";
        cout << "destination reached" << endl;
    }
public:
    void addEdge(int u, int v, bool direction) {
        if(direction)
            adjList[u].push_back(v);
        else {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }
    void get_graph() {
        return print_graph();
    }
    void get_order_DFS(int src, map<int, int> &vis, stack<int> &st) {
        return topological_sort_DFS(src, vis, st);
    }
    void get_order_BFS(int n, vector<int> &order) {
        return topological_sort_BFS(n, order);
    }
    void get_path(int src, int dest) {
        return shortest_path_BFS(src, dest);
    }
};

int main() {

    Graph g;
    int n, u, v, d;
    cout << "enter edges : ";
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter [u] [v] [d] : ";
        cin >> u >> v >> d;
        g.addEdge(u, v, d);
    }
    g.get_graph();

    int src, dest;
    cout << "enter [src] and [dest] : ";
    cin >> src >> dest;
    g.get_path(src, dest);

    // vector<int> order;
    // g.get_order_BFS(n, order);
    // if(n == order.size())
    //     cout << "no cycle present" << endl;
    // else    
    //     cout << "cycle present" << endl;

    // map<int, int> vis;
    // stack<int> st;
    // for(int node = 0; node < n; ++node) {
    //     if(!vis[node])
    //         g.get_order_DFS(node, vis, st);
    // }
    // cout << "printing topological order : " << endl << "[ ";
    // while(!st.empty()) {
    //     cout << st.top() << " ";
    //     st.pop();
    // }
    // cout << "]" << endl;

    return 0;
}