#include<bits/stdc++.h>

using namespace std;

// creation of graph :-
// adjacency matrix creation
vector<vector<int>> adjacency_matrix(vector<pair<int, int>> &edgelist) {
    vector<vector<int>> ans(edgelist.size(), vector<int>(edgelist.size(), 0));
    for(auto i : edgelist) {
        int v = i.first, u = i.second;
        ans[v][u] = 1;
    }
    return ans;
}

// adjacency list creation
class Graph{
public:
    unordered_map<int, list<int>> adjList;
    void addEdge(int u, int v, bool direction) {
        /*if [direction == 1] that means it's a directed
        graph => [u] se [v] ki taraf edge hai [u] -> [v]*/
        if(direction == 1) 
            adjList[u].push_back(v);
        else {
            /*if [direction == 0] that means it's an indirected
            graph => [u] se [v] ki taraf edge hogi or [v] se [u]
            ki taraf bhi [u] <--> [v]*/
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        cout << "printing adjList : " << endl;
        print_adjList();
    }

private:
    void print_adjList() {
        for(auto a : adjList) {
            cout << a.first << " -> [ ";
            for(auto b : a.second)
                cout << b << " ";
            cout << "]" << endl;
        }
    }
};

// adjacency list with weighted graph
template <typename T>
class WtGraph {
    void print_adjList() {
        for(auto a : adjList) {
            cout << a.first << " -> [ ";
            for(auto b : a.second)
                cout << "[ " << b.first << ", " << b.second << " ] ";
            cout << "]" << endl;
        }
    }

public:
    unordered_map<T, list<pair<T, int>>> adjList;
    void addEdge(T u, T v, int w, int direction) {
        if(direction)
            adjList[u].push_back(make_pair(v, w));
        else {
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});
        }
        cout << "printing adjList : " << endl;
        print_adjList();
    }

    // print graph int [BFS => breadth first sesarch] traversal
    void BFStraversal(T src, unordered_map<T, bool>& visited) {
        queue<T> q;
        q.push(src);
        visited[src] = 1;
        while(!q.empty()) {
            T front = q.front(); q.pop();
            cout << front << " ";
            for(auto a : adjList[front]) {
                T data = a.first;
                if(!visited[data]){
                    q.push(data);
                    visited[data] = 1;
                }
            }
        }
    }

    // print graph int [DFS => depth first sesarch] traversal
    void DFStraversal(T src, unordered_map<T, bool> &visited) {
        visited[src] = 1;
        cout << src << " ";
        for(auto a : adjList[src]) {
            T data = a.first;
            if(!visited[data])
                DFStraversal(data, visited);
        }
    }
};

int main() {

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<pair<int, int>> edgelist(n);
    for(int i=0; i<n; ++i) {
        cin >> edgelist[i].first;
        cin >> edgelist[i].second;
    }
    vector<vector<int>> result = adjacency_matrix(edgelist);
    for(auto const &row : result) {
        cout << "[ ";
        for(auto col : row)
            cout << col << " ";
        cout << "]" << endl;
    }

    Graph g;
    int n, s, e, flag;
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter the starting point : ";
        cin >> s;
        cout << "enter the ending point : ";
        cin >> e;
        cout << "directed or indirected : ";
        cin >> flag;
        g.addEdge(s, e, flag);
    }

    WtGraph<char> g;
    int n, w, flag;
    char s, e;
    cin >> n;
    for(int i=0; i<n; ++i) {
        cout << "enter the starting point : ";
        cin >> s;
        cout << "enter the ending point : ";
        cin >> e;
        cout << "enter the distance : ";
        cin >> w;
        cout << "directed or indirected : ";
        cin >> flag;
        g.addEdge(s, e, w, flag);
    }

    // printing in BFS => breadth first search
    /*by doing this if the nodes aren't connect or in a
    disconnected form then this method can't print all nodes*/
    // g.BFStraversal(char s);

    /*this is the better method to print all nodes even if those
    are in disconnected form*/
    unordered_map<char, bool> visited;
    int connected=0;
    for(char node = 'a'; node <= e; ++node) {
        if(!visited[node]) {
            connected++;
            g.BFStraversal(node, visited);
        }
    }
    cout << "no. of disconnected graphs : " << connected << endl;

    printing in DFS => depth first search
    unordered_map<char, bool> visited;
    for(char node = 'a'; node <= e; ++node) {
        if(!visited[node])
            g.DFStraversal(node, visited);
    }
    
    return 0;
}