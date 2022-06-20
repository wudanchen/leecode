/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-05 23:44:01
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-06 00:50:21
 * @FilePath: /swordFingerOffer/30offer.cpp
 * @Description: 定义栈的数据结构，
 * 请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，
 * 调用 min、push 及 pop 的时间复杂度都是 O(1)。
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include <iostream>
#include <stack>
#include <deque>
#include <algorithm>

using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
        m_deque.push_back(x);
    }
    
    void pop() {
        m_deque.pop_back();
    }
    
    int top() {
        return m_deque.back();
    }
    
    int min() {
        deque<int>::iterator it = min_element(m_deque.begin(), m_deque.end());
        return *it;
    }
private:
    deque<int> m_deque;
};

int main() {
    MinStack minStack;
    minStack.push(4);
    minStack.push(-3);
    minStack.push(-4);
    minStack.pop();
    cout << "min : " << minStack.min() << endl;
    return 0;
}