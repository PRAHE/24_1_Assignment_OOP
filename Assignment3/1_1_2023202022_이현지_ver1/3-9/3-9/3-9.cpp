#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    Node<T>* m_left;
    Node<T>* m_right;
    T m_Data;
    int depth;

public:
    Node() : m_left(nullptr), m_right(nullptr), m_Data(T()), depth(0) {}
    ~Node() {}

    void setData(T m_Data) { this->m_Data = m_Data; }
    void setDepth(int depth) { this->depth = depth; }
    void setLeft(Node<T>* m_left) { this->m_left = m_left; }
    void setRight(Node<T>* m_right) { this->m_right = m_right; }

    T getData() { return this->m_Data; }
    int getDepth() { return this->depth; }
    Node<T>* getLeft() { return this->m_left; }
    Node<T>* getRight() { return this->m_right; }
};

template <typename T>
class BST {
private:
    Node<T>* m_root;

public:
    BST() : m_root(nullptr) {}
    ~BST() { deleteTree(m_root); }

    void build(T arr[], int start, int end) {
        if (start > end) {
            return;
        }
        int mid = (start + end) / 2;
        insert(arr[mid]);
        build(arr, start, mid - 1);
        build(arr, mid + 1, end);
    }

    void insert(T n) {
        Node<T>* pNew = new Node<T>;
        pNew->setData(n);

        if (m_root == nullptr) {
            m_root = pNew;
        }
        else {
            Node<T>* curNode = m_root;
            Node<T>* parent = nullptr;

            while (true) {
                parent = curNode;
                if (n < curNode->getData()) {
                    curNode = curNode->getLeft();
                    if (curNode == nullptr) {
                        parent->setLeft(pNew);
                        return;
                    }
                }
                else if (n > curNode->getData()) {
                    curNode = curNode->getRight();
                    if (curNode == nullptr) {
                        parent->setRight(pNew);
                        return;
                    }
                }
            }
        }
    }

    void printTree() {
        printTreeRec(m_root, 0);
    }

private:
    void printTreeRec(Node<T>* node, int depth) {
        if (node == nullptr) {
            return;
        }

        printTreeRec(node->getRight(), depth + 1);

        for (int i = 0; i < depth; ++i) {
            cout << "  ";
        }
        cout << node->getData() << endl;

        printTreeRec(node->getLeft(), depth + 1);
    }

    void deleteTree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->getLeft());
        deleteTree(node->getRight());
        delete node;
    }
};

int main() {
    int arr[] = { 12, 21, 37, 46, 59, 65, 74, 83, 89, 94 };
    int size = sizeof(arr) / sizeof(arr[0]);
    BST<int> bst;

    bst.build(arr, 0, size - 1);

    bst.printTree();
}
