#ifndef ATOMIC_HPP
#define ATOMIC_HPP

#include <atomic>

extern std::atomic<bool> serverShutdown;
extern std::atomic<bool> clientExit;

#endif // ATOMIC_HPP