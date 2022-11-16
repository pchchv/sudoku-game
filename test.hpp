/*
Function declarations for unit-testing
*/

#pragma once
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "game.hpp"
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

template <typename TimeT> // template as measurement size (seconds, milliseconds)
struct measure
{
    template <typename F, typename... Args>
    static typename TimeT::rep execution(F func, Args &&...args)
    {
        auto start = chrono::high_resolution_clock::now();
        func(forward<Args>(args)...); // forward arguments to function
        auto duration = chrono::duration_cast<TimeT>(chrono::high_resolution_clock::now() - start);
        return duration.count();
    }
};

// Unit test
void unitTest(int size, int nobs, int ntimes, bool verbose);