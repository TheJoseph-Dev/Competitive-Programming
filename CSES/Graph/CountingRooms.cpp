#include <stdio.h>
#include <queue>

struct P {
    int x, y;

    P operator+(const P& other) const {
        return {this->x + other.x, this->y + other.y};
    }
};

P dirs[] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

bool inBounds(const P& p, int w, int h) {
    return 0 <= p.x && p.x < w && 0 <= p.y && p.y < h;
}

void bfs(const P& s, char map[1001][1001], bool visited[1001][1001], int w, int h) {
    std::queue<P> q = std::queue<P>();
    q.push(s);

    while(!q.empty()) {
        P p = q.front();
        q.pop();

        if(visited[p.y][p.x]) continue;
        visited[p.y][p.x] = true;

        for(int i = 0; i < 4; i++) {
            P nP = p+dirs[i];
            if(inBounds(nP, w, h) && map[nP.y][nP.x] == '.') q.push(nP);
        }
    }
}

int main() {

    int h, w;
    char map[1001][1001];
    scanf("%d%d", &h, &w);

    for(int i = 0; i < h; i++)
        scanf("%s", map[i]);

    bool visited[1001][1001] = {{0}};

    int rooms = 0;
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            if(!(map[i][j] == '.' && !visited[i][j])) continue;
            rooms++;

            bfs({j, i}, map, visited, w, h);
        }

    printf("%d\n", rooms);

    return 0;
}