#ifndef TIMER
#define TIMER

#include <memory>
#include <chrono>
#include <iostream>

class Timer {

    public:
        Timer();

        double ms;

        double Stop();

        std::chrono::time_point< std::chrono::high_resolution_clock> m_StartTimepoint;
};

#include "Timer.hpp"
#endif // DATA