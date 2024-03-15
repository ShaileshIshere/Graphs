#include<bits/stdc++.h>

using namespace std;

template<typename T>

struct Graph{
    unordered_map<T, list<T>> adjList;
    void addEdge(T u, T v, bool direction) {
        if(direction)
            adjList[u].push_back(v);
        else {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    // cycle detection
    // undirected graph : BFS
    bool check_cycle_un_BFS(T src, unordered_map<T, bool> &visited) {
        queue<T> q;
        unordered_map<T, T> parent;
        // initial state
        q.push(src);
        visited[src] = 1;
        parent[src] = -1;
        while(!q.empty()) {
            T front = q.front(); q.pop();
            for(auto node : adjList[front]) {
                if(!visited[node]) {
                    q.push(node);
                    visited[node] = 1;
                    parent[node] = front;
                }
                else if(visited[node] && node != parent[front])
                    return true;
            }
        }
        // cycle not present
        return false;
    }

    // undirected graph : DFS
    bool check_cycle_un_DFS(T src, unordered_map<int, bool> &visited, int parent) {
        visited[src] = 1;
        for(auto node : adjList[src]) {
            if(!visited[node]) {
                bool ans = check_cycle_un_DFS(node, visited, src);
                if(ans)
                    return true;
            }
            else if(visited[node] && node != parent)
                return true;
        }
        return false;
    }

    // directed graph : DFS
    bool check_cycle_directed_DFS(int src, unordered_map<int, bool> &vis, unordered_map<int, bool> &DFS) {
        vis[src] = 1;
        DFS[src] = 1;
        
        // recursion
        for(auto node : adjList[src]) {
            if(!vis[node]) {
                bool ans = check_cycle_directed_DFS(node, vis, DFS);
                if(ans)
                    return true;
            }
            if(vis[node] && DFS[node])
                return true;
        }
        
        // backtracking => most imp
        DFS[src] = 0;
        return false;
    }
};

int main() {

    Graph<int> g;
    int n, u, v, direction;
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter parent node, child node, directed or undirected : ";
        cin >> u >> v >> direction;
        g.addEdge(u, v, direction);
    }

    /*this method for checking cycle in graph is for normies
    in this method we can't check in disconnected graph*/
    // if(g.check_cycle_in_BFS(u))
    //     cout << "cycle present" << endl;
    // else 
    //     cout << "cycle absent" << endl;

    // this is the better option
    bool ans;
    unordered_map<int, bool> visited;
    unordered_map<int, bool> DFS;
    for(int i=0; i<n; ++i) {
        if(!visited[i]) {
            // ans = g.check_cycle_in_BFS(i, visited);
            // int parent = -1;
            // ans = g.check_cycle_un_DFS(i, visited, parent);
            ans = g.check_cycle_directed_DFS(i, visited, DFS);
        }
    }
    if(ans)
        cout << "cycle present" << endl;
    else 
        cout << "cycle absent" << endl;

    
     
    return 0;
}