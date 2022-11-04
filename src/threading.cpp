#include <threading.h>

void parallelize(const std::vector<std::function<void()>>& jobs,
	int n_threads) {
	// Copy of the jobs.
	std::vector<std::function<void()>> jobs_copy = jobs;
	std::mutex jobs_mutex;

	// Threads.
	std::vector<std::thread> threads;
	for (int i = 0; i < n_threads; i++) {
		threads.push_back(std::thread([&] {
			// Each thread runs this function.
			std::function<void()> job = [] {};
			bool done = false;

			// Keep taking jobs untile none is left.
			while (!done) {
				jobs_mutex.lock();

				if (jobs_copy.empty()) {
					// No jobs left.
					done = true;
				} else {
					// Take job.
					job = jobs_copy.back();
					jobs_copy.pop_back();
				}

				jobs_mutex.unlock();

				// Run job.
				job();
			}
		}));
	}

	// Wait for all threads to finish.
	for (int i = 0; i < n_threads; i++)
		threads[i].join();
}