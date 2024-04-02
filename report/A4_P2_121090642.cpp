
#include<iostream>
using namespace std;
#include<queue>
#include<array>


class MedianSearchTree {
public:
    MedianSearchTree(int n0, int k0): n(n0), k(k0) {
        bgsize = 0;
        smsize = 0;
        bgheap = vector<int>(n+k);
        smheap = vector<int>(n+k);
    }

    void bgInsert(int w) {
        bgsize++;
        int hole = bgsize;
        while (hole > 1 && w > bgheap[hole/2]) {
            bgheap[hole] = bgheap[hole/2];
            hole /= 2;
        }
        bgheap[hole] = w;
    }

    void smInsert(int w) {
        smsize++;
        int hole = smsize;
        while (hole > 1 && w < smheap[hole/2]) {
            smheap[hole] = smheap[hole/2];
            hole /= 2;
        }
        smheap[hole] = w;
    }

    void bgDown(int hole) {
        int tmp = bgheap[hole];
        int child;
        while (hole*2 <= bgsize) {
            child = hole*2;
            if (child != bgsize &&
                bgheap[child+1] > bgheap[child]) {
                    child++;
                }
            if (bgheap[child] > tmp) {
                bgheap[hole] = bgheap[child];
            } else {
                break;
            }
            hole = child;
        }
        bgheap[hole] = tmp;
    }

    void smDown(int hole) {
        int tmp = smheap[hole];
        int child;
        while (hole*2 <= smsize) {
            child = hole*2;
            if (child != smsize &&
                smheap[child+1] < smheap[child]) {
                    child++;
                }
            if (smheap[child] < tmp) {
                smheap[hole] = smheap[child];
            } else {
                break;
            }
            hole = child;
        }
        smheap[hole] = tmp;
    }

    int bgPop() {
        int data = bgheap[1];
        bgheap[1] = bgheap[bgsize];
        bgsize--;
        bgDown(1);
        return data;
    }

    int smPop() {
        int data = smheap[1];
        smheap[1] = smheap[smsize];
        smsize--;
        smDown(1);
        return data;
    }

    void insert(int w) {
        bgInsert(w);
        smInsert(bgPop());
        if (bgsize < smsize) {
            bgInsert(smPop());
        }
    }

    void outputMedian() {
        vector<int> output(2*k);
        for (int i = 0; i < k; i++) {
            output[k-i-1] = bgPop();
        }
        for (int i = k; i < 2*k; i++) {
            output[i] = smPop();
        }
        for (int i = 0; i < 2*k; i++) {
            cout << output[i] << " ";
            insert(output[i]);
        }
        cout << endl;
    }

    void bgDelete(int num) {
        vector<int> wait_lst(num);
        for (int i = 0; i < num; i++) {
            wait_lst[num-i-1] = bgPop();
        }
        for (int i = 1; i < num; i++) {
            bgInsert(wait_lst[i]);
        }
        if (bgsize < smsize) {
            bgInsert(smPop());
        }
    }

    void smDelete(int num) {
        vector<int> wait_lst(num);
        for (int i = 0; i < num; i++) {
            wait_lst[i] = smPop();
        }
        for (int i = 0; i < num-1; i++) {
            smInsert(wait_lst[i]);
        }
        if (bgsize - smsize == 2) {
            smInsert(bgPop());
        }
    }

    void deleteP(int p) {
        if ( 1<= p && p <= k) {
            bgDelete(k-p+1);
        } else {
            smDelete(p-k);
        }
    }

    int n;
    int k;
    int bgsize;
    int smsize;
    vector<int> bgheap;
    vector<int> smheap;
};

int main() {
    int n;
    int k;
    int order;
    int value;
    cin >> n >> k;
    MedianSearchTree solution(n, k);
    for (int i = 0; i < 2*k; i++) {
        cin >> value;
        solution.insert(value);
    }
    for (int i = 0; i < n; i++) {
        cin >> order;
        if (order == 1) {
            cin >> value;
            solution.insert(value);
        }
        if (order == 2) {
            solution.outputMedian();
        }
        if (order == 3) {
            cin >> value;
            solution.deleteP(value);
        }
    }
}