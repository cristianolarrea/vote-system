#include "Timer.h"

#include <memory>
#include <chrono>
#include <iostream>

Timer::Timer() {
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    auto endTimepoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
    auto duration = end - start;
    this->ms = duration * 100;
    std::cout << "Duração: " <<  ms << " ms. \n";
}