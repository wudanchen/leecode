/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-06-15 08:54:15
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-06-15 20:42:13
 * @FilePath: /swordFingerOffer/1117offer.cpp
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
#include <algorithm>

using namespace std;
//信号量解法
class H2O {
public:
    H2O() {
        sem_init(&m_semH1, 0, 1);
        sem_init(&m_semO, 0, 0);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&m_semH1);
        releaseHydrogen();
        ++hSize;
        if (hSize == 2) {
            hSize = 0;
            sem_post(&m_semO);
        }else {
            sem_post(&m_semH1);
        }
    }

    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&m_semO);
        releaseOxygen();
        sem_post(&m_semH1);
    }
private:
    sem_t m_semH1;
    sem_t m_semO;
    int hSize = 0;
};

//锁和条件变量
class H2OMutex {
public:
    H2OMutex() {
    }

    void hydrogen(function<void()> releaseHydrogen) {
        lock_guard<mutex> locker(m_mutex);
        while (hSize >= 2) {
            m_condVar.wait(m_mutex);
        }
        releaseHydrogen();
        ++hSize;
        m_condVar.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        lock_guard<mutex> locker(m_mutex);
        while(!(hSize == 2)) {
            m_condVar.wait(m_mutex);
        }
        releaseOxygen();
        hSize = 0;
        m_condVar.notify_all();
    }
private:
    mutex m_mutex;
    condition_variable_any m_condVar;
    int hSize = 0;
};

int main() {
    string waterStr;
    auto releaseHydrogen = [=] () {
        cout << "H";
    };
    auto releaseOxygen = [=] () {
        cout << "O";
    };
    while (cin >> waterStr) {
        if (waterStr == "end") {
            return 0;
        }
        bool res = true;
        for (const auto str : waterStr) {
            if (str != 'H' && str != 'O') {
                res = false;
                break;
            }
        }

        if (!res) {
            cout << "输入为 :"<< waterStr << ", 请重新输入" << endl;
            continue;
        }
        cout << "输入为 :"<< waterStr << endl;
        vector<thread> threadVector;
        H2OMutex h2o;
        cout << "输出为：";
        for_each(waterStr.begin(), waterStr.end(), [=, &threadVector, &h2o](char str){
            if (str == 'H') {
                threadVector.push_back(thread([=, &h2o]() {
                    h2o.hydrogen(releaseHydrogen);
                }));
            }else if (str == 'O') {
                threadVector.push_back(thread([=, &h2o]() {
                    h2o.oxygen(releaseOxygen);
                }));
            }
        });
        for_each(threadVector.begin(), threadVector.end(), [=](thread &t) {
            // cout << "thread id : " << t.get_id() << endl;
            t.join();
        });
        cout << endl;
    }
    return 0;
}