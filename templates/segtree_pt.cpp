#include <bits/stdc++.h>

template<typename Value>
struct SegTree
{
    typedef struct Node {
        Node* left;
        Node* right;

        int l, r;
        Value value;
    } Node;

    std::vector<Node> alloc;
    std::function<Value(Value, Value)> compute;
    Node* head;

    SegTree(int N, std::function<Value(Value, Value)> p_compute)
    {
        alloc.reserve(N * 4);
        compute = p_compute;
    }


    // @param pos: zero based index
    void update(int pos, Value val, Node* node = nullptr)
    {
        if (node == nullptr) node = head;

        if (node->l == node->r) {
            node->value = val;
            return;
        }

        int mid = node->l + (node->r - node->l) / 2;

        if (node->left == nullptr) {
            node->left = &alloc.emplace_back();
            node->left->l = node->l;
            node->left->r = mid;
        }

        if (node->right == nullptr) {
            node->right = &alloc.emplace_back();
            node->right->l = mid+1;
            node->right->r = node->r;
        }

        if (pos <= mid) {
            update(pos, val, node->left);
        } else {
            update(pos, val, node->right);
        }

        node->value = this->compute(node->left->value, node->right->value);
    }

    int query(int l, int r, Node* node = nullptr)
    {
        if (node == nullptr) {
            node = head;
        }

        int tl = node->l, tr = node->r;

        if (l > r) return 0;

        if (l <= tl && tr <= r) {
            return node->value;
        }

        return this->compute(query(l, std::min(node->left->r, r), node->left), query(std::max(l, node->right->l), r, node->right));
    }

    Node* build(std::vector<int>& values)
    {
        head = &alloc.emplace_back();
        head->l = 0;
        head->r = values.size()-1;

        int pos = 0;
        for (int val: values) {
            update(pos, val, head);
            pos++;
        }

        return head;
    }
};

int sum(int a, int b) {
    return a + b;
}

int compute_min(int a, int b) {
    return std::min(a, b);
}

using namespace std;
void example()
{
    int N = 1e3;
    using Tree = SegTree<int>;
    Tree min_tree(N, compute_min);
    Tree sum_tree(N, sum);

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = numbers.size();
    auto min_head = min_tree.build(numbers);
    auto sum_head = sum_tree.build(numbers);

    cout << min_tree.query(0, n-1) << '\n';
    cout << min_tree.query(0, n/2) << '\n';
    cout << min_tree.query(0, n/2 + n/4) << '\n';

    cout << sum_tree.query(0, n-1) << '\n';
    cout << sum_tree.query(0, n/2) << '\n';
    cout << sum_tree.query(0, n/2 + n/4) << '\n';
}

int32_t main(void)
{
    example();

    return 0;
}
