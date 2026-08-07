int ALPH = 26;

struct AhoCorasick {
    struct node {
        vector<int> to;
        vector<bool> trie;
        bool ter = false;
        int link = -1;
        int p = -1;
        int pc = -1;

        int suplink = -1;

        node() {
            to.resize(ALPH, -1);
            trie.resize(ALPH, false);
        }
    };

    vector<node> mem;

    AhoCorasick() {
        mem.resize(1);
    }

    void add_string(vector<int> s) {
        int v = 0;
        for (int c : s) {
            if (!mem[v].trie[c]) {
                int u = mem.size();
                mem[v].to[c] = u;
                mem.emplace_back();
                mem[u].p = v;
                mem[u].pc = c;
                mem[v].trie[c] = true;
            }
            v = mem[v].to[c];
        }
        mem[v].ter = true;
    }

    void build_automaton() {
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();

            if (v == 0 || mem[v].p == 0)
                mem[v].link = 0;
            else
                mem[v].link = mem[mem[mem[v].p].link].to[mem[v].pc];

            mem[v].suplink = mem[v].link;
            if (!mem[mem[v].link].ter)
                mem[v].suplink = mem[mem[v].link].suplink;

            for (int c = 0; c < ALPH; c++) {
                if (mem[v].trie[c])
                    Q.push(mem[v].to[c]);
                else if (v == 0)
                    mem[v].to[c] = 0;
                else
                    mem[v].to[c] = mem[mem[v].link].to[c];
            }
        }
    }
};
