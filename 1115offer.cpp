/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-14 19:47:53
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-15 03:47:18
 * @FilePath: /swordFingerOffer/1115offer.cpp
 * @Description: 
    两个不同的线程将会共用一个 FooBar 实例：
    线程 A 将会调用 foo() 方法，而
    线程 B 将会调用 bar() 方法
    请设计修改程序，以确保 "foobar" 被输出 n 次。
    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/print-foobar-alternately
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <semaphore.h>
#include <future>
#include <string>

using namespace std;

class Base {
public:
    virtual void foo(function<void()> printFoo) = 0;
    virtual void bar(function<void()> printBar) = 0;
};
//信号
class SemaphoreFooBar : public Base {
public:
    SemaphoreFooBar(int n)
    : n(n) {
        sem_init(&m_semt1, 0, 1);
        sem_init(&m_semt2, 0, 0);
    }
    void foo(function<void()> printFoo) override {
        for (int i = 0; i < n; i++) {
            sem_wait(&m_semt1);
            printFoo();
            sem_post(&m_semt2);
        }
    }
    void bar(function<void()> printBar) override {
        for (int i = 0; i < n; i++) {
            sem_wait(&m_semt2);
            printBar();
            sem_post(&m_semt1);
        }
    }
private:
    int n;
    sem_t m_semt1;
    sem_t m_semt2;
};

//锁和条件变量方法
class FooBar : public Base {
public:
    FooBar(int n) {
        this->n = n;
        this->sortFlag = First;
    }

    void foo(function<void()> printFoo) override {
        lock_guard<mutex> lock(m_mutex);
        for (int i = 0; i < n; i++) {
            m_condVar1.wait(m_mutex, [=]() {
                return sortFlag == First;
            });
            printFoo();
            sortFlag = Second;
            m_condVar1.notify_one();
        }
    }

    void bar(function<void()> printBar) override {
        lock_guard<mutex> lock(m_mutex);
        for (int i = 0; i < n; i++) {
            m_condVar1.wait(m_mutex, [=]() {
                return sortFlag == Second;
            });
        	printBar();
            sortFlag = First;
            m_condVar1.notify_one();
        }
    }

private:
    enum SortFlag {
        First = 0,
        Second = 1
    };
    int n;
    int sortFlag = First;
    mutex m_mutex;
    condition_variable_any m_condVar1;
};

int main() {
    string numStr;
    while(cin >> numStr) {
        if (numStr == "end") {
            return 0;
        }
        int num = atoi(numStr.data());
        cout << "输入 num  :" << num << endl; 
        // shared_ptr<Base> fooBar(new FooBar(num));
        shared_ptr<Base> fooBar(new SemaphoreFooBar(num));
        #if 0
        thread t1([=, &fooBar]() {
            fooBar->foo([=](){printf("foo");});
        });
        thread t2([=, &fooBar]() {
            fooBar->bar([=](){printf("bar");});
        });
        t1.join();
        t2.join();
        #else
        future<void> t1 = async(launch::async, [=, &fooBar]() {
            fooBar->foo([=](){printf("Foo");});
        });
        future<void> t2 = async(launch::async, [=, &fooBar]() {
            fooBar->bar([=](){printf("bar");});
        });
        t1.wait();
        t2.wait();
        #endif
        cout << endl;
    }
    return 0;
}