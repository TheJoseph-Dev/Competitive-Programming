#include <stdio.h>
#include <queue>
#include <string>
#include <algorithm>

struct P {
    int x, y;

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


P dirs[] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

bool inBounds(const P& p, int w, int h) {
    return 0 <= p.x && p.x < w && 0 <= p.y && p.y < h;
}

char d2c(const P& dir) {
    if(dir.x == 1 && dir.y == 0) return 'R';
    if(dir.x == 0 && dir.y == 1) return 'D';
    if(dir.x == 0 && dir.y == -1) return 'U';
    if(dir.x == -1 && dir.y == 0) return 'L';
    return ' ';
}

P c2d(char ch) {
    if(ch == 'R') return {1,0};
    if(ch == 'D') return {0,1};
    if(ch == 'U') return {0,-1};
    if(ch == 'L') return {-1,0};
    return {0,0};
}

char parent[1001][1001];
std::string findPath(const P& start, const P& end, char map[1001][1001], int w, int h) {
    std::queue<P> q = std::queue<P>();
    q.push(start);

    bool visited[1001][1001] = {{0}};
    
    while(!q.empty()) {
        P p = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            P nP = p+dirs[i];
            if(inBounds(nP, w, h) && map[nP.y][nP.x] != '#' && !visited[nP.y][nP.x]) {
                 visited[nP.y][nP.x] = true;
                 parent[nP.y][nP.x] = d2c(dirs[i]);
                 q.push(nP);
            }
        }
    }

    std::string path = "";
    P tracer = end;
    if(visited[end.y][end.x]) {
        while(tracer != start) {
            path += parent[tracer.y][tracer.x];
            tracer = tracer-c2d(parent[tracer.y][tracer.x]);
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int main() {

    int h, w;
    char map[1001][1001];
    scanf("%d%d", &h, &w);

    for(int i = 0; i < h; i++)
        scanf("%s", map[i]);

    P A, B;
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            if(map[i][j] == 'A') A = {j, i};
            else if(map[i][j] == 'B') B = {j, i};

    std::string path = findPath(A, B, map, w, h);

    if(path == "") puts("NO");
    else printf("YES\n%d\n%s", path.size(), path.c_str());

    return 0;
}