class Solution {
public:
    static const int MAXK = 5;

    struct Node {
        int prod = 1;
        array<int, MAXK> cnt{};
    };

    int K;
    vector<Node> seg;

    Node mergeNode(const Node& L, const Node& R) {
        Node res;
        res.prod = (int)(1LL * L.prod * R.prod % K);
        for (int i = 0; i < K; i++) {
            res.cnt[i] = L.cnt[i];
        }
        for (int r = 0; r < K; r++) {
            int newRem = (int)(1LL * L.prod * r % K);
            res.cnt[newRem] += R.cnt[r];
        }

        return res;
    }

    void build(int idx, int l, int r, vector<int>& nums) {
        if (l == r) {
            seg[idx] = Node();

            int rem = nums[l] % K;

            seg[idx].prod = rem;
            seg[idx].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, nums);
        build(idx * 2 + 1, mid + 1, r, nums);

        seg[idx] = mergeNode(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            seg[idx] = Node();

            int rem = val % K;

            seg[idx].prod = rem;
            seg[idx].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(idx * 2, l, mid, pos, val);
        } else {
            update(idx * 2 + 1, mid + 1, r, pos, val);
        }

        seg[idx] = mergeNode(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql == l && qr == r) {
            return seg[idx];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(idx * 2, l, mid, ql, qr);
        }

        if (ql > mid) {
            return query(idx * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(idx * 2, l, mid, ql, mid);

        Node right = query(idx * 2 + 1, mid + 1, r, mid + 1, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {

        K = k;

        int n = nums.size();
        seg.assign(4 * n + 5, Node());
        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];
            update(1, 0, n - 1, index, value);
            Node cur = query(1, 0, n - 1, start, n - 1);
            ans.push_back(cur.cnt[x]);
        }

        return ans;
    }
};