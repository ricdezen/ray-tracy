#ifndef THREADING_H
#define THREADING_H

#include <functional>
#include <mutex>
#include <thread>
#include <vector>

/**
 * @param jobs Set of jobs to run in parallel. Not modified, copied.
 * @param threads Maximum concurrent threads.
 */
void parallelize(const std::vector<std::function<void()>> &jobs, int n_threads);

#endif