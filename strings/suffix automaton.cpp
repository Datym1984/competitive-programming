const int ALPH = 26;

struct SA {
    struct Node {
        int to[ALPH];
        int link = -1;
        int len = 0;

        Node() {
            fill(to, to + ALPH, -1);
        }
    };

    vector<Node> mem;
    int head = 0;

    SA() {
        mem.resize(1);
    }

    void extend(int c) {
        int new_head = mem.size();
        mem.emplace_back();
        mem[new_head].len = mem[head].len + 1;
        for (; head != -1; head = mem[head].link) {
            if (mem[head].to[c] == -1) {
                mem[head].to[c] = new_head;
                continue;
            }
            if (mem[head].len + 1 == mem[mem[head].to[c]].len) {
                mem[new_head].link = mem[head].to[c];
                break;
            }
            int v = mem[head].to[c];
            int vc = mem.size();
            mem.push_back(mem[v]);
            mem[v].link = vc;
            mem[vc].len = mem[head].len + 1;
            while (head != -1 && mem[head].to[c] == v) {
                mem[head].to[c] = vc;
                head = mem[head].link;
            }
            mem[new_head].link = vc;
            break;
        }
        if (mem[new_head].link == -1)
            mem[new_head].link = 0;
        head = new_head;
    }
};
