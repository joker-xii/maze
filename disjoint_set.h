#ifndef GAME_DS_DISJOINT_SET_H
#define GAME_DS_DISJOINT_SET_H

struct disjoint_set {
    std::vector<int> parent;

    explicit disjoint_set(int n_total) : parent(n_total) {
        for (int i = 0; i < n_total; ++i) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_set(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (x != y)parent[y] = x;
    }

};

#endif //GAME_DS_DISJOINT_SET_H
