/* ==========================================================================
 * Title : 트리 순회(Tree Travesal)
 * Author : starrykss
 * Date : 2021.05.22
 * Reference : 코딩 테스트를 위한 자료 구조와 알고리즘 with C++ (길벗)
 * ==========================================================================*/ 

#include <iostream>
#include <queue>

struct node {
    std::string position;
    node* first;
    node* second;
};

struct org_tree {
    node* root;

    static org_tree create_org_structure(const std::string& pos) {
        org_tree tree;
        tree.root = new node {pos, NULL, NULL};
        return tree;
    }

    static node* find(node* root, const std::string& value) {
        ////// 1. 루트 노드가 존재하지 않을 경우
        if (root == NULL) {
            return NULL;
        }

        ////// 2. 루트 노드가 존재할 경우
        //// (1) 루트 노드에 찾고자 하는 값이 있을 경우
        if (root->position == value) {
            return root;
        }

        //// (2) 루트 노드에 찾고자 하는 값이 없을 경우
        // [1] 왼쪽 서브 트리 검사
        auto firstFound = org_tree::find(root->first, value);   

        if (firstFound != NULL) {
            return firstFound;
        }

        // [2] 오른쪽 서브 트리 검사
        return org_tree::find(root->second, value);   
    }

    bool addSubordinate(const std::string& manager, const std::string& subordinate) {
        auto managerNode = org_tree::find(root, manager);

        //// 1. 부하 직원 추가 실패
        // 상사 직원이 없을 경우
        if (!managerNode) {
            std::cout << manager << "을(를) 찾을 수 없습니다: " << std::endl;
            return false;
        }

        // 상사 직원 밑에 이미 2명의 부하 직원이 있을 경우
        if (managerNode->first && managerNode->second) {
            std::cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다." << std::endl;
            return false;
        }

        //// 2. 부하 직원 추가 성공
        // 상사 직원 밑에 부하 직원이 없을 경우
        if (!managerNode->first) {    // (1) 첫번째(first) 부하 직원이 없을 경우
            managerNode->first = new node {subordinate, NULL, NULL};
        }
        else {    // (2) 2번째(second) 부하 직원이 없을 경우
            managerNode->second = new node {subordinate, NULL, NULL};
        }
        std::cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다." << std::endl;

        return true;
    }

    static void preOrder(node* start) {
        if (!start) {
            return;
        }
        std::cout << start->position <<", ";    // (C)
        preOrder(start->first);                 // (L)
        preOrder(start->second);                // (R)
    }

    static void inOrder(node* start) {
        if (!start) {
            return;
        }
        inOrder(start->first);                  // (L)
        std::cout << start->position << ", ";   // (C)
        inOrder(start->second);                 // (R)
    }

    static void postOrder(node* start) {
        if (!start) {
            return;
        }
        postOrder(start->first);                // (L)
        postOrder(start->second);               // (R)
        std::cout << start->position << ", ";   // (C)
    }

    static void levelOrder(node* start) {
        if (!start) {
            return;
        }

        std::queue<node*> q;
        q.push(start);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto current = q.front();
                q.pop();

                std::cout << current->position << ", ";
                if (current->first) {
                    q.push(current->first);
                }
                if (current->second) {
                    q.push(current->second);
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    auto tree = org_tree::create_org_structure("CEO");

    // 노드 추가
    std::cout << "[노드 추가]" << std::endl;
    tree.addSubordinate("CEO", "부사장");
    tree.addSubordinate("부사장", "IT부장");
    tree.addSubordinate("부사장", "마케팅부장");
    tree.addSubordinate("IT부장", "보안팀장");
    tree.addSubordinate("IT부장", "앱개발팀장");
    tree.addSubordinate("마케팅부장", "물류팀장");
    tree.addSubordinate("마케팅부장", "홍보팀장");

    std::cout << std::endl;

    // 전위 순회
    std::cout << "[전위 순회]" << std::endl;
    org_tree::preOrder(tree.root);
    std::cout << std::endl << std::endl;

    // 중위 순회
    std::cout << "[중위 순회]" << std::endl;
    org_tree::inOrder(tree.root);
    std::cout << std::endl << std::endl;

    // 후위 순회    
    std::cout << "[후위 순회]" << std::endl;
    org_tree::postOrder(tree.root);
    std::cout << std::endl << std::endl;

    // 레벨 순서 순회
    std::cout << "[레벨 순서 순회]" << std::endl;
    org_tree::levelOrder(tree.root);
    std::cout << std::endl << std::endl;

    return 0;
}