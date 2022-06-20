#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {

    }
};

class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> intVector;        
        for (ListNode *node = head; node ; node = node->next) {
            intVector.push_back(node->val);
        }
        
        reverse(intVector.begin(), intVector.end());
        return intVector;
    }
    ListNode* reverseList(ListNode* head) {
        
        ListNode *pre = nullptr;
        for(ListNode *cur = head, *temp;cur; cur = temp) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
        }
        return pre;
    }
};

int main() {
    ListNode *four = new ListNode(4);
    ListNode *three = new ListNode(3);
    ListNode *two = new ListNode(2);
    ListNode *head = new ListNode(1);
    head->next = two;
    two->next = three;
    three->next = four;
    Solution solution;

    // vector<int> intVector = solution.reversePrint(head);
    // for (int node : intVector) {
    //     cout << node << ", ";
    // }
    // cout << endl;
    ListNode *reverse = solution.reverseList(head);
    for (ListNode *node = reverse; node; node = node->next) {
        cout << node->val << ",";
    }
    cout << endl;
    return 0;
}