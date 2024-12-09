#include <stdio.h>
#include <vector>
#include <queue>
 
#define INF 1002001
 
struct P {
    int x, y;
 
    P(int x = 0, int y = 0): x(x), y(y) {}
 
    P operator+(const P& other) const {
        return {this->x + other.x, this->y + other.y};
    }
 
    P operator-(const P& other) const {
        return {this->x - other.x, this->y - other.y};
    }
 
    bool operator!=(const P& other) const {
        return !(this->x == other.x && this->y == other.y);
    }
};
 
P dirs[4] = {{0,1}, {1,0}, {-1,0}, {0,-1}};
 
bool inBounds(const P& p, int w, int h) {
    return 0 <= p.x && p.x < w && 0 <= p.y && p.y < h;
}
 
int dist[1001][1001];
void MonsterBFS(const std::vector<P>& monsters, char map[1001][1001], int w, int h) {
 
    std::queue<P> q = std::queue<P>();
    for(auto& m : monsters) {
        dist[m.x][m.y] = 0;
        q.push(m);
    }
 
    while(!q.empty()) {
        P pos = q.front();
        q.pop();
 
        for(int i = 0; i < 4; i++) {
            P next = pos+dirs[i];
            if(!inBounds(next, w, h) || map[next.y][next.x] == '#' || dist[next.x][next.y] <= dist[pos.x][pos.y] + 1) continue;
            dist[next.x][next.y] = dist[pos.x][pos.y] + 1;
            q.push(next);
        }
    }
}
 
struct Node {
    P pos;
    int depth;
};
 
bool AtEdge(const P& p, int w, int h) {
    return p.x == 0 || p.x == w-1 || p.y == 0 || p.y == h-1;
}
 
char pos2ch(const P& pos) {
    if(pos.x == 1 && pos.y == 0) return 'R';
    if(pos.x == -1 && pos.y == 0) return 'L';
    if(pos.x == 0 && pos.y == 1) return 'D';
    if(pos.x == 0 && pos.y == -1) return 'U';
    return ' ';
}
 
P parent[1001][1001];
void ExitBFS(const P& src, char map[1001][1001], int w, int h) {
    bool visited[1001][1001] = {{false}};
    std::queue<Node> q = std::queue<Node>();
    q.push({src, 0});
 
    while(!q.empty()) {
        Node node = q.front();
        q.pop();
 
        if(AtEdge(node.pos, w, h)) {
            printf("YES\n%d\n", node.depth);
            std::vector<char> path = std::vector<char>();
            P tracker = node.pos;
            while(tracker != src) {
                path.push_back(pos2ch(tracker - parent[tracker.x][tracker.y]));
                tracker = parent[tracker.x][tracker.y];
            }
 
            for(int i = path.size()-1; i >= 0; i--) putchar(path[i]);
            return;
        }
 
        for(int i = 0; i < 4; i++) {
            P next = node.pos+dirs[i];
            if(!inBounds(next, w, h) || visited[next.x][next.y] || map[next.y][next.x] == '#' || node.depth+1 >= dist[next.x][next.y]) continue;
            visited[next.x][next.y] = true;
            parent[next.x][next.y] = node.pos;
            q.push({next, node.depth+1});
        }
    }
 
    puts("NO");
}
 
int main() {
 
    int h, w;
    scanf("%d%d", &h, &w);
 
    char map[1001][1001];
    for(int i = 0; i < h; i++)
        scanf("%s", map[i]);
 
    P A;
    std::vector<P> monsters;

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            dist[j][i] = INF;
            if(map[i][j] == 'A') A = {j, i};
            else if(map[i][j] == 'M') monsters.emplace_back(j, i);
        }
 
    MonsterBFS(monsters, map, w, h);
    ExitBFS(A, map, w, h);

    return 0;
}