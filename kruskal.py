class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])
    
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def apply_union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1
    
    def kruskal_algo(self):
        result = []
        i, e = 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2])
        parent = []
        rank = []
        for node in range(self.V):
            parent.append(node)
            rank.append(0)
        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.apply_union(parent, rank, x, y)
        print('\n[INFO] Here are the results.\n')
        for u, v, weight in result:
            print("%d - %d: %d" % (u, v, weight))

def main():
    try:
        ver = int(input(f'\n[INPUT] Enter the number of Vertices for Graph: '))
    except ValueError:
        print(f'\n[ERROR] INVALID INPUT.')
        main()
    grhp(ver)

def grhp(ver):
    ghp = Graph(ver)
    try:
        ed_num = int(input(f'\n[INPUT] Enter the number of Edges for Graph: '))
    except ValueError:
        print(f'\n[ERROR] INVALID INPUT.')
        grph(ver)
    for i in range(1, ed_num + 1):
        ed_1, ed_2, ed_3 = input(f'[INPUT] Enter edge {i} in format `<edge1> <edge2> <edge3>: ').split()
        ghp.add_edge(int(ed_1), int(ed_2), int(ed_3))
    
    ghp.kruskal_algo()

if __name__ == '__main__':
    main()