#pragma once
#include <mutex>

class DataLock {
public:
	DataLock() {
		mutex.lock();
	};
	~DataLock() {
		mutex.unlock();
	};
private:
	std::mutex mutex;
};
