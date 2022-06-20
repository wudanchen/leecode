/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-05 00:11:37
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-05 08:37:15
 * @FilePath: /swordFingerOffer/09offer.cpp
 * @Description: 用两个栈实现队列
 * 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
 * 分别完成在队列尾部插入整数和在队列头部删除整数的功能。
 * (若队列中没有元素，deleteHead 操作返回 -1 )
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include <iostream>
#include <stack>
#include <deque>


class CQueue {
public:
    CQueue() {

    }
    /*
    ** 在队列尾部插入整数
    */
    void appendTail(int value) {
        m_stack.push(value);
    }
    //在队列头部删除整数(若队列中没有元素，deleteHead 操作返回 -1 )
    int deleteHead() {
        if (m_stack.empty()) {
            return -1;
        }
        for (;!m_stack.empty(); m_stack.pop()) {
            m_stackTemp.push(m_stack.top());
        }
        m_stackTemp.pop();
        for (;!m_stackTemp.empty(); m_stackTemp.pop()) {
            m_stack.push(m_stackTemp.top());
        }
        return 1;
    }
    void printf() {
        for (;!m_stack.empty(); m_stack.pop()) {
            std::cout << m_stack.top() << ",";
        }
    }
private:
    std::stack<int> m_stack;
    std::stack<int> m_stackTemp;
};

class CQueueTwo {
public:
    CQueueTwo() {

    }
    /*
    ** 在队列尾部插入整数
    */
    void appendTail(int value) {
        m_stack1.push(value);
    }
    //在队列头部删除整数(若队列中没有元素，deleteHead 操作返回 -1 )
    int deleteHead() {
        if (m_stack1.empty() && m_stack2.empty()) {
            return -1;
        }
        int value = -1;
        if(!m_stack2.empty()) {
            value = m_stack2.top();
            m_stack2.pop();
        }else if(!m_stack1.empty()) {
            for(; !m_stack1.empty(); m_stack1.pop()) {
                m_stack2.push(m_stack1.top());
            }
            value = m_stack2.top();
            m_stack2.pop();
        }
        return value;
    }
private:
    std::stack<int> m_stack1;
    std::stack<int> m_stack2;
};

int main() {
    CQueueTwo cqueue;
    cqueue.appendTail(3);
    // cqueue.deleteHead();
    // cqueue.deleteHead();
    // cqueue.deleteHead();
    // cqueue.printf();
    return 0;
}