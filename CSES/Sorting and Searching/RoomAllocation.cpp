#include <stdio.h>
#include <queue>
#include <algorithm>

struct Room {
    int checkout, room;

    bool operator<(const Room& other) const {
        return this->checkout > other.checkout;
    }
};

struct Customer {
    int a, b, id, room;
};

bool byID(const Customer& lhs, const Customer& rhs) {
    return lhs.id < rhs.id;
}


bool byArrival(const Customer& lhs, const Customer& rhs) {
    return lhs.a < rhs.a;
}

int main() {

    int n;
    scanf("%d", &n);

    int maxRoom = 1;
    std::vector<Customer> customers = std::vector<Customer>(n);
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &customers[i].a, &customers[i].b);
        customers[i].id = i;
    }

    std::sort(customers.begin(), customers.end(), byArrival);

    std::priority_queue<Room> roomsPool;
    for(int i = 0; i < n; i++) {
        if(roomsPool.empty()) {
            roomsPool.push({customers[i].b, 1});
            customers[i].room = 1;
            continue;
        }
        
        Room r = roomsPool.top();
        if(r.checkout < customers[i].a) roomsPool.pop();
        else r.room = (int)roomsPool.size()+1;
        
        maxRoom = std::max(maxRoom, r.room);
        customers[i].room = r.room;
        r.checkout = customers[i].b;
        roomsPool.push(r);
    }
    
    std::sort(customers.begin(), customers.end(), byID);

    printf("%d\n", maxRoom);
    for(auto [a, b, id, r] : customers)
        printf("%d ", r);

    return 0;
}