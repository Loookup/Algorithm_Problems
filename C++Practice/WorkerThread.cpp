//
// Created by 이철용 on 2022/07/05.
//

#include "WorkerThread.h"
#include <thread>

void WorkerThread::readWorker() {
    size_t size = SharedPreferences::getInstance().size();
    std::lock_guard<std::mutex> map_locker(mu);
    answers.emplace_back(&SharedPreferences::getInstance());
    //std::cout << "read by key: " << &SharedPreferences::getInstance() << " " << size << " " << SharedPreferences::getInstance().getInt("key") << std::endl;
}

void WorkerThread::writeWorker(int value) {
    //auto preferences = SharedPreferences::getInstance();
    SharedPreferences::getInstance().putInt("key", value);
    size_t size = SharedPreferences::getInstance().size();
    std::lock_guard<std::mutex> map_locker(mu);
    answers.emplace_back(&SharedPreferences::getInstance());
    //std::cout << "write by key: " << &SharedPreferences::getInstance() << " " << size << " " << value << std::endl;
}

void WorkerThread::play() {
    WorkerThread workerThread;
    // std::cerr << "h/w cores: " << std::thread::hardware_concurrency() << std::endl;
    std::thread threads[8];
    for(int i=0; i < 8; i+=2) {
        threads[i] = std::thread ([=] { writeWorker(i); });
        threads[i + 1] = std::thread ([=] { readWorker(); });
    }

    for (int i=0; i < 8; i++) {
        threads[i].join();
    }

    if(std::all_of(std::cbegin(answers), std::cend(answers), [=](const auto& e) {return e == &SharedPreferences::getInstance();}))
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
}
