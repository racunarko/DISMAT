import numpy as np

n = int(input("Unesite prirodan broj n: "))
a = int(input("Unesite prirodan broj a: "))
b = int(input("Unesite prirodan broj b: "))
c = int(input("Unesite prirodan broj c: "))

G = np.zeros((n, n), dtype=int)

for i in range(1, n + 1):
    for j in range(1, n + 1):
        weight = 0
        if i < j:
            weight = np.floor(abs(a * i - b * j) / c)
        elif j < i:
            weight = np.floor(abs(b * i - a * j) / c)
        if weight != 0:
            G[i - 1][j - 1] = weight

# print(G)


def connected(G):
    for u in range(n):
        visited = [False] * n
        traverse(G, u, visited)
        for i in range(n):
            if not visited[i]:
                return False
    return True


def traverse(G, u, visited):
    visited[u] = True
    for v in range(n):
        if G[u][v] and (not visited[v]):
            traverse(G, v, visited)


# print(connected(G))


def max_spanning_tree(graph):
    # Primov algoritam
    infinity = 9999999

    mst = np.zeros((n, n), dtype=int)
    # maximum spanning tree
    selected = [False] * n

    # number of edges, always less than V - 1
    num_edge = 0

    # odabirem vrh 1
    selected[0] = True

    while num_edge < n - 1:
        minimum = infinity
        x = 0
        y = 0
        for i in range(n):
            if selected[i]:
                for j in range(n):
                    if (not selected[j]) and graph[i][j]:
                        if minimum > graph[i][j]:
                            minimum = graph[i][j]
                            x = i
                            y = j
        mst[x][y] = 1
        mst[y][x] = 1
        selected[y] = True
        num_edge += 1
    return mst


def prufer(mst, num_vertices):
    prufer_code = []
    mst_copy = mst.copy()

    while num_vertices > 2:
        for i in range(n):
            if sum(mst_copy[i]) == 1:
                for j in range(n):
                    if mst_copy[i][j] == 1:
                        prufer_code.append(j + 1)
                        mst_copy[i][j] = mst_copy[j][i] = 0
                        num_vertices -= 1
                break
    return prufer_code


MST = []
code = []
string = "nije"
if connected(G):
    string = "je"
    MST = max_spanning_tree(G)
    code = prufer(MST, n)
print("Graf G ", string, " povezan graf")
print("Pruferov kod minimalnog razapinjuceg stabla: ", code)
# print(MST)
# print(code)
