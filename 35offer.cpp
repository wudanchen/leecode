/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-06 07:51:18
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-06 08:29:51
 * @FilePath: /swordFingerOffer/35offer.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include <iostream>

using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return head;
        }
        Node *temp;
        Node *curNode = head;
        while(curNode) {
            Node *nextNode = new Node(curNode->next->val);
            nextNode->next = 

            Node *random = new Node(curNode->random->val);

            

            curNode = curNode->next;
        }
        return backup;
    }
};

int main() {
    return 0;
}