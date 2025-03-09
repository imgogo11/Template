# Splay

```c++
struct Splaytree {
    static inline int ch[N][2], fa[N], siz[N], cnt[N], val[N], node_tot;
    int root;
    Splaytree() : root(0) {}
    void pushup(int x) { siz[x] = siz[ch[x][0]] + cnt[x] + siz[ch[x][1]]; }
    void rotate(int x) {
        int y = fa[x], d = ch[y][0] == x;
        fa[ch[y][1 ^ d] = ch[x][d]] = y;
        if (fa[y]) ch[fa[y]][ch[fa[y]][1] == y] = x;
        fa[x] = fa[y], ch[x][d] = y, fa[y] = x;
        pushup(y);
    }
    void splay(int x, int guard) {
        if (!x) return;
        for (int y; (y = fa[x]) != guard; rotate(x)) {
            if (fa[y] != guard) rotate((ch[fa[y]][0] == y ^ ch[y][0] == x) ? x : y);
        }
        pushup(x);
        if (!guard) root = x;
    }
    int join(int x, int y) { // assum that keys in x < keys in y
        if (!x || !y) return x | y;
        while (ch[x][1]) x = ch[x][1];
        splay(x, 0);
        fa[ch[x][1] = y] = x;
        pushup(x);
        return x;
    }
    void insert(int v) {
        int x = root, y = 0;
        while (x) {
            y = x;
            if (v != val[x]) {
                x = ch[x][v > val[x]];
            } else {
                ++cnt[x];
                splay(x, 0);
                return;
            }
        }
        if (!y) {
            root = ++node_tot;
        } else {
            ch[y][v > val[y]] = ++node_tot;
        }
        fa[node_tot] = y, val[node_tot] = v, cnt[node_tot] = 1;
        splay(node_tot, 0);
    }
    void del(int v) { // assume that v is in the tree
        int x = root;
        while (val[x] != v) x = ch[x][v > val[x]];
        --siz[x];
        if (!--cnt[x]) {
            fa[ch[x][0]] = fa[ch[x][1]] = 0;
            if (fa[x]) {
                int y = fa[x], d = ch[y][1] == x;
                fa[ch[y][d] = join(ch[x][0], ch[x][1])] = y;
                splay(y, 0);
            } else {
                root = join(ch[x][0], ch[x][1]);
            }
        } else {
            splay(x, 0);
        }
    }
    int rank(int v) {
        int x = root, ans = 0, y = 0;
        while (x) {
            y = x;
            if (v > val[x]) {
                ans += siz[ch[x][0]] + cnt[x];
                x = ch[x][1];
            } else if (v == val[x]) {
                ans += siz[ch[x][0]];
                break;
            } else {
                x = ch[x][0];
            }
        }
        splay(y, 0);
        return ans;
    }
    int kth(int k) { // k must > 0 and <= the size of the tree
        int x = root;
        while (k <= siz[ch[x][0]] || k > siz[ch[x][0]] + cnt[x]) {
            if (k <= siz[ch[x][0]]) {
                x = ch[x][0];
            } else {
                k -= siz[ch[x][0]] + cnt[x], x = ch[x][1];
            }
        }
        splay(x, 0);
        return val[x];
    }
    int pred(int v) {
        int x = root, ans = -0x3f3f3f3f, y = 0;
        while (x) {
            y = x;
            if (val[x] < v) {
                ans = val[x];
                x = ch[x][1];
            } else {
                x = ch[x][0];
            }
        }
        splay(y, 0);
        return ans;
    }
    int succ(int v) {
        int x = root, ans = 0x3f3f3f3f, y = 0;
        while (x) {
            y = x;
            if (val[x] > v) {
                ans = val[x];
                x = ch[x][0];
            } else {
                x = ch[x][1];
            }
        }
        splay(y, 0);
        return ans;
    }
} t;
```

