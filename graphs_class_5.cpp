#include<bits/stdc++.h>

using namespace std;

class Solution {
    // Course Schedule - LC(207)
    // using [BFS]
    void topological_sort_BFS(int n, vector<int> &order, unordered_map<int, list<int> > &adjList) {
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
    // using [DFS]
    bool topological_sort_DFS(int src, unordered_map<int, int>& vis, vector<int> &order, unordered_map<int, list<int>>& adjList) {
        vis[src] = 1;
        for (auto nbr : adjList[src]) {
            if (vis[nbr] == 0) {
                return topological_sort_DFS(nbr, vis, order, adjList);
            } else if (vis[nbr] == 1) {
                return false;
            }
        }
        vis[src] = 2;
        order.push_back(src);
        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, list<int> > adjList;
        for(vector<int> i : prerequisites) {
            int u = i[0];
            int v = i[1];
            adjList[u].push_back(v);
        }

        vector<int> order;
        unordered_map<int, int> vis;

        topological_sort_BFS(numCourses, order, adjList);
        if(order.size() == numCourses)
            return true;
        else
            return false;

        for(int node = 0; node < numCourses; ++node) {
            if(!vis[node]) {
                if(!topological_sort_DFS(node, vis, order, adjList))
                    return false;
            }
        }
        return order.size() == numCourses;
    }

    // path with minimum effort - LC(1631)
    bool isSafe(int newX, int newY, int row, int col,vector<vector<int> >& diff, int currX, int currY ) {
        if(newX >=0 && newY >=0 && newX < row && newY < col && diff[currX][currY] < diff[newX][newY]) {
            return true;
        }
        else {
            return false;
        }
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        priority_queue< pair<int, pair<int,int> > , vector<pair<int,pair<int,int> > >, greater<pair<int,pair<int,int> > > > mini;
        int row = heights.size();
        int col = heights[0].size();
        vector<vector<int> > diff(row, vector<int>(col, INT_MAX));
        int destX = row-1;
        int destY = col-1;
        //initial state
        //set srcn ka distance 0
        diff[0][0] = 0;
        //min heap meentry for src push krdo
        mini.push({0,{0,0}});

        while(!mini.empty()) {
            auto topPair = mini.top();
            mini.pop();
            int currDiff = topPair.first;
            pair<int,int>  currNodeIndexPair = topPair.second;
            int currX = currNodeIndexPair.first;
            int currY = currNodeIndexPair.second;
            //cout << "CurrDiff: " << currDiff << " currX " << currX <<" currY " << currY << endl;
            
            //now we can travel to all nbr i.e. top, down, left, right
            int dx[] = {-1,0,1,0};
            int dy[] = {0,1,0,-1};
            for(int i=0; i<4; i++) {
                //cout << "Inside for loop for currX " << currX << " currY " << currY  << endl;
                int newX = currX + dx[i];
                int newY = currY + dy[i];
                if(isSafe(newX, newY,row,col,diff,currX, currY)) {
                    //cout << "Inside safe if condition with currX " << currX << " currY " << currY << endl;
                    //cout << " newX " << newX << " newY " << newY << endl; 
                    int maxDiff = max(currDiff, abs(heights[currX][currY]-heights[newX][newY]));
                    //check can we update diff array
                    diff[newX][newY] = min(diff[newX][newY], maxDiff);
                    //cout << "diff updated " << diff[newX][newY] << endl;
                    //entry create karo min Heap me
                    if(newX != destX || newY != destY) {
                        mini.push({diff[newX][newY], {newX, newY}});
                        //cout << "new entry added " << endl;
                    }
                }
            }
        }
        return diff[destX][destY];
    }
};

int main() {

    Solution s;

    int numCourses, n, m;
    cout << "enter the no. of courses : ";
    cin >> numCourses;
    cout << "enter [n] and [m] : ";
    cin >> n >> m;
    vector<vector<int>> prerequisites(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j)
            cin >> prerequisites[i][j];
    }
    if(s.canFinish(numCourses, prerequisites))
        cout << "yes, we can finish these courses" << endl;
    else
        cout << "No, we can't finish these courses" << endl;

    int n, m;
    cout << "enter [n] and [m] : ";
    cin >> n >> m;
    vector<vector<int>> heights(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) 
            cin >> heights[i][j];
    }
    cout << "minimum effort req to travel : " << s.minimumEffortPath(heights) << endl;
     
    return 0;
}