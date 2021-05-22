/* ==========================================================================
 * Title : 이진 탐색 트리(Binary Search Tree)
 * Author : starrykss
 * Date : 2021.05.22
 * Reference : 코딩 테스트를 위한 자료 구조와 알고리즘 with C++ (길벗)
 * ==========================================================================*/ 

#include <iostream>

struct node {
    int data;
    node* left;
    node* right;
};

struct bst {
    node* root = nullptr;

    node* find(int value) {
        return find_impl(root, value);
    }

private:
    node* find_impl(node* current, int value) {
        // 노드가 존재하지 않을 경우
        if (!current) {
            std::cout << std::endl;
            return NULL;
        }

        // value 값이 현재 노드에 있는 경우
        if (current->data == value) {
            std::cout << value << "을(를) 찾았습니다. " << std::endl;
            return current;
        }

        // value 값이 현재 노드 왼쪽에 있는 경우
        if (value < current->data) {
            std::cout << current->data << "에서 왼쪽으로 이동: ";
            return find_impl(current->left, value);
        }

        // value 값이 현재 노드 오른쪽에 있는 경우
        std::cout << current->data <<"에서 오른쪽으로 이동: ";
        return find_impl(current->right, value);
    }

public:
    void insert(int value) {
        if (!root) {                                // 1. 루트 노드가 없을 경우
            root = new node {value, NULL, NULL};
        }
        else {                                      // 2. 루트 노드가 있을 경우
            insert_impl(root, value);
        }
    }

private:
    void insert_impl(node* current, int value) {
        if (value < current->data) {                                //// 1. 왼쪽 서브 트리에 원소를 삽입해야 할 경우
            if (!current->left) {                                   // (1) 왼쪽 자식 노드가 존재하지 않을 경우
                current->left = new node {value, NULL, NULL};
            }
            else {                                                  // (2) 왼쪽 자식 노드가 존재할 경우
                insert_impl(current->left, value);
            }
        }
        else {                                                      //// 2. 오른쪽 서브 트리에 원소를 삽입해야 할 경우
            if (!current->right) {                                  // (1) 오른쪽 자식 노드가 존재하지 않을 경우
                current->right = new node {value, NULL, NULL};
            }
            else {                                                  // (2) 오른쪽 자식 노드가 존재할 경우
                insert_impl(current->right, value);
            }
        }
    }

public:
    void inorder() {
        inorder_impl(root);
    }

private:
    void inorder_impl(node* start) {
        if (!start) {
            return;
        }
        inorder_impl(start->left);                  // 왼쪽 서브 트리 방문
        std::cout << start->data << " ";            // 현재 노드 출력
        inorder_impl(start->right);                 // 오른쪽 서브 트리 방문
    }

public:
    node* successor(node* start) {
        auto current = start->right;                // 오른쪽 서브 트리로 이동
        while (current && current->left) {          // 왼쪽 하위 노드가 존재할 때까지 계속 반복
            current = current->left;                // 왼쪽의 하위 노드를 후속 노드로 설정
        }
        return current;
    }

	void deleteValue(int value) {
    	root = delete_impl(root, value);
	}

private:
    node* delete_impl(node* start, int value) {
        // 노드가 없을 경우
        if (!start) {
            return NULL;
        }

        if (value < start->data) {                              // (1) 삭제하고자 하는 원소가 현재 노드의 왼쪽 서브 트리에 있을 경우
            start->left = delete_impl(start->left, value);
        }
        else if (value > start->data) {                         // (2) 삭제하고자 하는 원소가 현재 노드의 오른쪽 서브 트리에 있을 경우
            start->right = delete_impl(start->right, value);
        }
        else {                                                  // (3) 삭제하고자 하는 원소가 현재 노드에 있을 경우
            // 자식 노드가 전혀 없거나, 왼쪽 자식 노드만 없는 경우
            if (!start->left) {
                auto tmp = start->right;
                delete start;
                return tmp;
            }

            // 오른쪽 자식 노드만 없는 경우
            if (!start->right) {
                auto tmp = start->left;
                delete start;
                return tmp;
            }

            // 자식 노드가 둘 다 있는 경우
            auto succNode = successor(start);
            start->data = succNode->data;

            // 오른쪽 서브 트리에서 후속(successor)을 찾아 삭제
            start->right = delete_impl(start->right, succNode->data);
        }

        return start;
    }
};

int main() {
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    std::cout << "중위 순회: ";
    tree.inorder();                     // BST의 모든 원소를 오름차순으로 출력
    std::cout << std::endl;

    tree.deleteValue(12);
    std::cout << "12를 삭제한 후 중위 순회: ";
    tree.inorder();                     // BST의 모든 원소를 오름차순으로 출력
    std::cout << std::endl;

    if (tree.find(12)) {
        std::cout << "원소 12는 트리에 있습니다." << std::endl;
    }
    else {
        std::cout << "원소 12는 트리에 없습니다." << std::endl;
    }

    return 0;
}