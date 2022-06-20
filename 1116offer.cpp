/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-15 05:45:52
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-15 08:28:55
 * @FilePath: /swordFingerOffer/1116offer.cpp
 * @Description: 
 * 
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

class ZeroEvenOdd {
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&printOdd, 0, 0);
        sem_init(&printEven, 0, 0);
        sem_init(&numDone, 0, 1);
    }

    // printNumber(x) outputs "x", where x is an integer.
    //输出0
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; ++i) {
            sem_wait(&numDone);
            printNumber(0);
            if (i % 2 == 0) {
                sem_post(&printEven);
            } else {
                sem_post(&printOdd);
            }
        }
    }
    //输出偶数
    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            sem_wait(&printEven);
            printNumber(i);
            sem_post(&numDone);
        }
    }
    //输出奇数
    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <=n; i += 2) {
            sem_wait(&printOdd);
            printNumber(i);
            sem_post(&numDone);
        }
    }
private:
    int n;
    sem_t printOdd, printEven, numDone;
};

int main() {
    auto printNumber = [] (int x) {
        cout << x;
    };
    string numStr;
    while (cin >> numStr) {
        if (numStr == "end") {
            return 0;
        }
        int num = atoi(numStr.data());
        cout << "输入参数: " << num << endl;
        shared_ptr<ZeroEvenOdd> zeroEvenOdd(new ZeroEvenOdd(num));
        thread t1([=]() {
            zeroEvenOdd->zero(printNumber);
        });
        thread t2([=]() {
            zeroEvenOdd->odd(printNumber);
        });
        thread t3([=]() {
            zeroEvenOdd->even(printNumber);
        });
        t1.join();
        t2.join();
        t3.join();
        cout << endl;
    }
    return 0;
}