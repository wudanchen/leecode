/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-15 23:23:26
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-19 22:50:27
 * @FilePath: /swordFingerOffer/1195offer.cpp
 * @Description: 交替打印字符串
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
#include <algorithm>
#include <atomic>

using namespace std;
class FizzBuzz {
public:
    FizzBuzz(int n) {
        this->n = n;
        // sem_init(&m_semFizz, 0, 0);
        // sem_init(&m_semBuzz, 0, 0);
        // sem_init(&m_semFizzbuzz, 0, 0);
    }

    // printFizz() outputs "fizz".
    //fizz() 来判断是否能被 3 整除，如果可以，则输出 fizz。
    void fizz(function<void()> printFizz) {
        lock_guard<mutex> locker(m_mutex);
        while (currentNum <= n) {
            while ((currentNum <=n) && !(currentNum % 3 == 0 && currentNum % 5 != 0)) {
                // cout << "(FIZZ wait start.)" << endl;
                m_condVar.wait(m_mutex);
                // cout << "(FIZZ wait end.)" << endl;
            }
            if (currentNum > n) {
                // m_condVar.notify_all();
                break;
            }
            printFizz();
            ++currentNum;
            m_condVar.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    //buzz() 来判断是否能被 5 整除，如果可以，则输出 buzz。
    void buzz(function<void()> printBuzz) {
        lock_guard<mutex> locker(m_mutex);
        while (currentNum <= n) {
            while ((currentNum <=n) && !(currentNum % 5 == 0 && currentNum % 3 != 0)) {
                // cout << "(BUZZ wait start.)" << endl;
                m_condVar.wait(m_mutex);
                // cout << "(BUZZ wait end.)" << endl;
            }
            if (currentNum > n) {
                // m_condVar.notify_all();
                break;
            }
            printBuzz();
            ++currentNum;
            m_condVar.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    //fizzbuzz() 来判断是否同时能被 3 和 5 整除，如果可以，则输出 fizzbuzz
	void fizzbuzz(function<void()> printFizzBuzz) {
        lock_guard<mutex> locker(m_mutex);
        while (currentNum <= n) {
            while ((currentNum <=n) && !(currentNum % 3 == 0 && currentNum % 5 == 0)) {
                // cout << "(FIZZBUZZ wait start.)" << endl;
                m_condVar.wait(m_mutex);
                // cout << "(FIZZBUZZ wait end.)" << endl;
            }
            if (currentNum > n) {
                // m_condVar.notify_all();
                break;
            }
            printFizzBuzz();
            ++currentNum;
            m_condVar.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    //number() 来实现输出既不能被 3 整除也不能被 5 整除的数字。
    void number(function<void(int)> printNumber) {
        lock_guard<mutex> locker(m_mutex);
        while (currentNum <= n) {
            while ((currentNum <=n) && !(currentNum % 3 != 0 && currentNum %5 != 0)) {
                // cout << "(NUMBER wait start.)" << endl;
                m_condVar.wait(m_mutex);
                // cout << "(NUMBER wait end.)" << sendl;
            }
            if (currentNum > n) {
                // m_condVar.notify_all();
                break;
            }
            printNumber(currentNum);
            ++currentNum;
            m_condVar.notify_all();
        }
    }
private:
    int n;
    int currentNum = 1;
    mutex m_mutex;
    condition_variable_any m_condVar;
    // sem_t m_semFizz;
    // sem_t m_semBuzz;
    // sem_t m_semFizzbuzz;
};

int main() {
    string numStr;
    while (cin >> numStr) {
        if (numStr == "end") {
            return 0;
        }
        int num = atoi(numStr.data());
        cout << "输入参数: " << num << endl;
        cout << "输出： ";
        
        FizzBuzz fizzBuzz(num);
        thread ta([=, &fizzBuzz]() {
            fizzBuzz.fizz([=]() {printf("fizz");});
        });
        thread tb([=, &fizzBuzz] () {
            fizzBuzz.buzz([=]() {printf("buzz");});
        });
        thread tc([=, &fizzBuzz](){
            fizzBuzz.fizzbuzz([=](){printf("fizzbuzz");});
        });
        thread td([=, &fizzBuzz]() {
            fizzBuzz.number([=](int x){cout << x;});
        });
        ta.join();
        // cout << "ta join endl" << endl;
        tb.join();
        // cout << "tb join endl" << endl;
        tc.join();
        // cout << "tc join endl" << endl;
        td.join();
        // cout << "td join endl" << endl;
        cout << endl;
    }
    return 0;

}