#include <stdio.h>
#include <vector>

class Graph {

    int v;
    std::vector<std::vector<int>> adj;

public:

    Graph(int v): v(v), adj(std::vector<std::vector<int>>(v)) {}
    
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

private:
    bool DFS(int s, bool visited[100001], int teams[100001]) {
        std::vector<int> stk = std::vector<int>();
        stk.push_back(s);

        while(!stk.empty()) {
            int node = stk.back();
            stk.pop_back();

            if(visited[node]) continue;
            visited[node] = true;

            for(auto e : this->adj[node]) {
                int opTeam = (teams[node] == 1 ? 2 : 1);
                if(teams[e] && teams[e] != opTeam) return false;
                teams[e] = opTeam;
                stk.push_back(e);
            }
        }

        return true;
    }

    bool SetConnectedComponents(int teams[100001]) {
        bool visited[100001] = {false};
        for(int i = 1; i < this->v; i++) {
            if(visited[i]) continue;
            teams[i] = 1;
            if(!this->DFS(i, visited, teams)) return false;
        }

        return true;
    };

public:

    void BuildTeams() {
        int teams[100001] = {0};
        if(!this->SetConnectedComponents(teams)) {
            puts("IMPOSSIBLE");
            return;
        }

        for(int i = 1; i < this->v; i++)
            printf("%d ", teams[i]);
    }
};



int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n+1);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a, b);
    }

    graph.BuildTeams();

    return 0;
}