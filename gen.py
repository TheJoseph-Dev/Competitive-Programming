import random
import sys
import collections

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
random.seed(seed)

def ri(l, r):
    return random.randint(l, r)

def array(n, l, r):
    return [ri(l, r) for _ in range(n)]

n = ri(20000, 20000)
a = ri(1, n)
b = ri(a, n)
print(f"{n} {a} {b}")
arr = [ri(0, 1000000) for _ in range(n)]
#for c in arr: print(c, sep='', end='')
print(*arr)

exit(0)
n = ri(1, 10)
m = ri(0, int(n*(n-1)/2))
print(n, m)

adj = collections.defaultdict(list)
for i in range(n): adj[i] = []
for i in range(m):
    p = array(2, 1, n)
    while p[0] == p[1]: p = array(2,1,n)
    print(*p)
    adj[p[0]].append(p[1])

good = False
for i in range((1<<n)):
    if good == True: break
    b1 = []
    b2 = []
    for b in range(n):
        if(i & (1<<b) > 0):
            b1.append(b+1)
        else:
            b2.append(b+1)

    good = True
    for v in b1:
        for e in adj[v]:
            if(i & (1<<(e-1)) > 0): good = False

    for v in b2:
        for e in adj[v]:
            if((~i) & (1<<(e-1)) > 0): good = False

if good: print("P")
else: print("IMP")
# python3 gen.py > input.txt