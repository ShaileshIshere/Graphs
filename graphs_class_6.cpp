#include<bits/stdc++.h>

using namespace std;

class Solution {
    void dfs(int src, unordered_map<int, bool> &vis, int n, vector<vector<int>> &isConnected) {
        vis[src] = true;
        int row = src, col = n;
        for(int nbrIndex = 0; nbrIndex < n; ++nbrIndex) {
            if(isConnected[row][nbrIndex] == 1) {
                if(!vis[nbrIndex]) 
                    dfs(nbrIndex, vis, n, isConnected);
            }
        }
    }

    bool isSafe(int i, int j, vector<vector<char>> &grid, map<pair<int, int>, bool> &vis){
        int n = grid.size();
        int m = grid[0].size();
        if (i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '1' && !vis[{i, j}])
            return true;
        return false;
    }
    void bfs(int i, int j, vector<vector<char>> &grid, map<pair<int, int>, bool> &vis){
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[{i, j}] = true;
        while (!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int tempX = frontNode.first;
            int tempY = frontNode.second;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};
            for (int k = 0; k < 4; k++){
                int newX = tempX + dx[k];
                int newY = tempY + dy[k];
                if (isSafe(newX, newY, grid, vis)){
                    q.push({newX, newY});
                    vis[{newX, newY}] = true;
                }
            }
        }
    }

    bool isSafe(int x, int y, int old, vector<vector<int>> &ans) {
        if(x >= 0 && x < ans.size() && y >= 0 && y < ans[0].size() && ans[x][y] == old)
            return true;
        else
            return false;
    }
    void dfs(int oldColor, int newColor, vector<vector<int>> &ans, int sr, int sc) {
        ans[sr][sc] = newColor;
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        for(int i=0; i<4; ++i) {
            int newX = sr + dx[i];
            int newY = sc + dy[i];
            if(isSafe(newX, newY, oldColor, ans))
                dfs(oldColor, newColor, ans, newX, newY);
        }
    }
public:
    // no. of provinced - LC(547)
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), count = 0;
        unordered_map<int, bool> vis;
        for(int i=0; i<n; ++i) {
            if(!vis[i]) {
                dfs(i, vis, n, isConnected);
                count++;
            }
        }   
        return count;
    }

    // no. of islands - LC(200)
    int numIslands(vector<vector<char>> &grid){
        map<pair<int, int>, bool> vis;
        int count = 0;
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (!vis[{i, j}] && grid[i][j] == '1'){
                    bfs(i, j, grid, vis);
                    count++;
                }
            }
        }
        return count;
    }

    // flood fill - LC(733)
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        vector<vector<int>> ans = image;
        int oldColor = image[sr][sc];
        int newColor = color;
        if(oldColor == newColor)
            return ans;
        dfs(oldColor, newColor, ans, sr, sc);
        return ans;  
    }
};

int main() {

    Solution s;

    int n;
    cout << "enter [n] : ";
    cin >> n;
    vector<vector<int>> isConnected(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j)
            cin >> isConnected[i][j];
    }
    cout << "No. of provinces are : " << s.findCircleNum(isConnected) << endl;

    int n, m;
    cout << "enter [n] and [m] : ";
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j)
            cin >> grid[i][j];
    }
    cout << "no. of islands : " << s.numIslands(grid) << endl;

    int n, m, sr, sc, color;
    cout << "enter [sr], [sc] and [color] : ";
    cin >> sr >> sc >> color;
    cout << "enter [n] and [m] : ";
    cin >> n >> m;
    vector<vector<int>> img(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j)  
            cin >> img[i][j]; 
    }
    vector<vector<int>> result = s.floodFill(img, sr, sc, color);
    // print the image after flooding
    cout << "image after flood filling : " << endl << "[ ";
    for(auto &row:result) {
        cout << "[ ";
        for(auto &ele: row)
            cout << ele << " ";
        cout << "]";
    }
    cout << " ]" << endl;
     
    return 0;
}