//
//  main.cpp
//  CPPTest
//
//  Created by Lei zhang on 2017-10-09.
//  Copyright © 2017 lei zhang. All rights reserved.
//

#include <iostream>
#include <map>

using namespace std;

class DisjointSet {
public:
    DisjointSet(int n) {
        this->n = n;
        for (int i = 1; i <= n; i++) {
            makeNode(i);
        }
    }

    ~DisjointSet() {
        auto it = nodes.begin();
        auto end = nodes.end();
        for(; it != end; ++it) {
            delete it->second;
        }
    }

    void query(int data) {
        if (nodes[data] != nullptr) {
            cout << findRoot(nodes[data])->total << endl;
        }
    }

    void merge(int data1, int data2) {
        if (data1 > n || data2 > n) {
            return;
        }

        if (data1 == data2) {
            return;
        }

        Node* r1 = findRoot(nodes[data1]);
        Node* r2 = findRoot(nodes[data2]);

        if (r1 == r2) {
            return;
        }

        int result = r1->compareRange(r2);

        switch (result) {
            case 1:
                // range1 > range2
                r2->parent = r1;
                r1->total += r2->total;
                break;
            case 2:
                // range1 == range2
                r2->parent = r1;
                r1->total += r2->total;
                r1->range += 1;
                break;
            default:
                // range2 < range2
                r1->parent = r2;
                r2->total += r1->total;
                break;
        }
    }


private:
    struct Node {
        long data;
        int range;
        int total;
        Node* parent;

        Node(long d) {
            data = d;
            total = 1;
            range = 0;
            parent = nullptr;
        }

        int compareRange(const Node* rhs) const {
            if (range > rhs->range) {
                return 1;
            }
            else if (range < rhs->range) {
                return -1;
            }
            else {
                return 0;
            }
        }

        bool operator==(const Node* rhs) const  {
            return range == rhs->range && data == rhs->data;
        }
    };

    int n;
    map<long, Node*> nodes;


private:
    Node* makeNode(long data) {
        Node* node = new Node(data);
        nodes[data] = node;

        return node;
    }

    Node* findRoot(Node* node) {
        Node* current = node;

        while(current->parent != nullptr) {
            current = current->parent;
        }

        if (current != node) {
            node->parent = current;
        }

        return current;
    }


};



int main() {
    int n, q;
    cin >> n >> q;

    DisjointSet set = DisjointSet(n);

    char operation = 0;
    for(int i = 0; i < q; i++) {
        cin >> operation;
        if (operation == 'Q') {
            //query
            int data;
            cin >> data;
            set.query(data);
        }
        if (operation == 'M') {
            // merge
            int data1, data2;
            cin >> data1 >> data2;
            set.merge(data1, data2);
        }
    }

    return 0;
}



