#include <stdio.h>
#include <algorithm>

/*
Let's first solve the problem for two tasks and then we can extend it
to all the tasks. Assume we have two tasks T1 and T2:

    If we perform T1 before T2, reward = (deadline(T1) - duration(T1)) + (deadline(T2) - duration(T1) - duration(T2)). So, reward1 = deadline(T1) + deadline(T2) - 2 * duration(T1) - duration(T2)
    If we perform T2 before T1, reward = (deadline(T2) - duration(T2)) + (deadline(T1) - duration(T2) - duration(T1)). So, reward2 = deadline(T1) + deadline(T2) - 2 * duration(T2) - duration(T1)

From the above two formulas, 
we can say that the rewards will only differ according
to the values of duration(T1) and duration(T2) and 
are independent of whether deadline(T1) is greater or deadline(T2). 
Since the duration of the task performed earlier is subtracted
more times (twice) as compared to the duration of task performed
later, we can conclude that the tasks with smaller
 duration should be performed first. 
*/

constexpr int maxN = 2e5+1;

struct Task {
    int len, deadline;

    bool operator<(const Task& other) const {
        return this->len < other.len;
    }
};

int main() {

    int n;
    scanf("%d", &n);

    Task tasks[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d%d", &tasks[i].len, &tasks[i].deadline);
    
    std::sort(tasks, tasks+n);

    long long reward = 0;
    long long time = 0;
    for(int i = 0; i < n; i++) {
        time += tasks[i].len;
        reward += (tasks[i].deadline - time);
    }

    printf("%lld\n", reward);

    return 0;
}