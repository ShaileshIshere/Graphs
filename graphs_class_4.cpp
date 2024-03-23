#include<bits/stdc++.h>

using namespace std;

class Graph{
    unordered_map<int, list<pair<int, int> > > adjList;
    bool vis;

    void print() {
        for(auto i : adjList) {
            cout << i.first << " -> [ ";
            for(auto j : i.second) 
                cout << "[ " << j.first << ", " << j.second << " ]";
            cout << " ]" << endl;
        }
    }

    void topological_sort_DFS(int src, unordered_map<int, int> &vis, stack<int> &st) {
        vis[src] = true;

        for(auto nbr : adjList[src]) {
            if(!vis[nbr.first])
                topological_sort_DFS(nbr.first, vis, st);
        }

        st.push(src);
    }

    void shortest_path_dfs(stack<int> &st, int n) {
        vector<int> dist(n, INT_MAX);

        // initial node case
        int src = st.top(); st.pop();
        dist[src] = 0;

        for(auto nbrPair : adjList[src]) {
            int nbrnode = nbrPair.first;
            int nbrdist = nbrPair.second;
            if(dist[src] + nbrdist < dist[nbrnode])
                dist[nbrnode] = dist[src] + nbrdist;
        }

        while(!st.empty()) {
            int src = st.top(); st.pop();
            for(auto nbrPair : adjList[src]) {
                int nbrnode = nbrPair.first;
                int nbrdist = nbrPair.second;
                if(dist[src] + nbrdist < dist[nbrnode])
                    dist[nbrnode] = dist[src] + nbrdist;
            }
        }

        cout << "shortest distance for all nodes : " << endl << "[ ";
        for(auto i : dist)
            cout << i << " ";
        cout << "]" << endl;
    } 

    void dijkstra_shortest_distance(int n, int src, int dest) {
        vector<int> dist(n+1, INT_MAX);
        set<pair<int, int> > st;

        // initial state
        st.insert({0, src});
        dist[src] = 0;

        while(!st.empty()) {
            pair<int, int> top_pair = *st.begin();
            int top_dist = top_pair.first;
            int top_node = top_pair.second;
            // remove the top node from set
            st.erase(st.begin());

            // update distance of other nodes
            for(auto nbrPair : adjList[top_node]) {
                int nbr_node = nbrPair.first;
                int nbr_dist = nbrPair.second;
                if(top_dist + nbr_dist < dist[nbr_node]) {
                    // here we found a shorter distance than before
                    // now we've to update this in set
                    auto previous_entry = st.find({dist[nbr_node], nbr_node});
                    if(previous_entry != st.end())
                        st.erase(previous_entry);
                    
                    // now we're gonna update the dist array for the shorter distance
                    dist[nbr_node] = top_dist + nbr_dist;
                    st.insert({dist[nbr_node], nbr_node});
                }
            }
        }
        cout << "shortest distance from " << src << " node to " << dest << " node is : " << dist[dest] << endl;
    }
public:
    void addEdge(int u, int v, int w, bool direction) {
        if(direction)
            adjList[u].push_back({v, w});
        else {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
    }
    void print_graph() {
        return print();
    }
    void get_order(int src, unordered_map<int, int> &vis, stack<int> &st) {
        return topological_sort_DFS(src, vis, st);
    }
    void get_distance(stack<int> &st, int n) {
        return shortest_path_dfs(st, n);
    }
    void get_dijkstra(int n, int src, int dest) {
        return dijkstra_shortest_distance(n, src, dest);
    }
};

int main() {

    Graph g;
    int n, u, v, w, direction;
    cout << "enter the no. of edges : ";
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter [u] [v] [w] [d] : ";
        cin >> u >> v >> w >> direction;
        g.addEdge(u, v, w, (bool)direction);
    }
    g.print_graph();

    // unordered_map<int, int> vis;
    // stack<int> st;
    // int src;
    // cout << "enter [src] node : ";
    // cin >> src;
    // g.get_order(src, vis, st);
    // int size = st.size();
    // g.get_distance(st, size);
    
    int src, dest;
    cout << "enter source and destination nodes : ";
    cin >> src >> dest;
    g.get_dijkstra(n, src, dest);
     
    return 0;
}