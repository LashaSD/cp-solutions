#include <cstdio>
#include <ios>
#include <iostream>
#include <algorithm>
#include <cstdint>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

#define int ll

typedef struct node {
    node* next;
    node* prev;
    int value;
} node;

typedef struct {
    node* head;
    node* tail;

    int sum;
    int count;
} block;

const int maxN = 2e5;

node list[maxN + 5] = {0};
int pt = 0;

void block_append(block& blk, int value)
{
    blk.count++;
    if (blk.count == 1) {
        node* node = &list[pt++];
        node->value = value;
        blk.head = node;
    } else if (blk.count == 2) {
        node* node = &list[pt++];
        node->value = value;
        blk.tail = node;
        blk.head->next = node;
        node->prev = blk.head;
    } else {
        node* node = &list[pt++];
        node->value = value;
        blk.tail->next = node;
        node->prev = blk.tail;
        blk.tail = node;
    }

    blk.sum += value;
}

void block_append(block& blk, node* new_tail)
{
    blk.count++;
    if (blk.head == nullptr) {
        blk.head = new_tail;
    } else if (blk.tail == nullptr) {
        blk.head->next = new_tail;
        blk.tail = new_tail;
        blk.tail->prev = blk.head;
    } else {
        blk.tail->next = new_tail;
        new_tail->prev = blk.tail;
        blk.tail = new_tail;
    }
    blk.sum += new_tail->value;
}

void block_append_front(block& blk, node* new_head)
{
    blk.sum += new_head->value;
    blk.count++;
    if (blk.head == nullptr) {
        blk.head = new_head;
        new_head->next = nullptr;
    } else {
        blk.head->prev = new_head;
        new_head->next = blk.head;
        if (blk.count == 2) {
            blk.tail = blk.head;
        }
    }

    blk.head = new_head;
    new_head->prev = nullptr;
}

node* block_pop_front(block& blk)
{
    node* node = blk.head;

    if (node != nullptr) {
        blk.head = node->next;

        if (node->next != nullptr) {
            blk.head->prev = nullptr;
        }

        blk.sum -= node->value;
    } else {
        blk.sum = 0;
    }

    blk.count = max(0ll, blk.count - 1);

    return node;
}

node* block_pop_back(block& blk)
{
    if (blk.tail != nullptr) {
        node* last = blk.tail;

        if (last->prev != nullptr && blk.count > 2) {
            blk.tail = last->prev;
            blk.tail->next = nullptr;
        } else {
            blk.tail = nullptr;
        }

        blk.count--;
        blk.sum -= last->value;
        return last;
    } else {
        node* last = blk.head;
        blk.head = nullptr;

        blk.count--;
        if (last != nullptr) {
            blk.sum -= last->value;
        }
        dbg("HERE");
        return last;
    }
}

// G. Chimpanzini Bananini
void solve()
{
    int n;
    scanf("%lld", &n);
    dbg(n);
    // block l = {0}, r = {0};
    block b = {0};
    int ans = 0;
    int m = 0;
    bool reversed = false;

    for (int i = 0; i < n; ++i) {
        int query;
        scanf("%lld", &query);
        if (query == 1) {
            if (!reversed) {
                int val = 0;
                if (b.tail != nullptr) {
                    val = b.tail->value;
                } else if (b.head != nullptr) {
                    val = b.head->value;
                }

                ans += (b.sum - val) - (val * (m-1));
                block_append_front(b, block_pop_back(b));
            } else {
                int val = b.head == nullptr ? 0 : b.head->value;
                ans += (b.sum - val) - (val * (m-1));
                dbg("HER");
                block_append(b, block_pop_front(b));
                dbg("2");
            }
        } else if (query == 2) {
            ans = (b.sum * (m+1)) - ans;
            reversed = !reversed;
        } else if (query == 3) {
            int value;
            scanf("%lld", &value);

            ++m;
            if (!reversed) {
                block_append(b, value);
            } else {
                node* node = &list[pt++];
                node->value = value;
                block_append_front(b, node);
            }

            ans += value * m;
        }

        printf("%lld\n", ans);
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    scanf("%lld", &T);
    while(T--)
        solve();
    return 0;
}
