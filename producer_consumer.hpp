#ifndef jm4R_PRODUCER_CONSUMER
#define jm4R_PRODUCER_CONSUMER

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

namespace mj {

template <typename Product>
struct producer_consumer {
public:
    producer_consumer(std::function<void(Product&&)> consumer)
        : _consumer{ std::move(consumer) }
    {
    }

    void start()
    {
        _stopped = false;
        _thread = std::thread{ [&] { consume(); } };
    }

    void stop()
    {
        {
            std::lock_guard<std::mutex> lk(_mutex);
            _stopped = true;
        }
        _cv.notify_all();
        if (_thread.joinable())
            _thread.join();
    }

    void push(Product p)
    {
        {
            std::lock_guard<std::mutex> lk(_mutex);
            _products.push(std::move(p));
        }
        _cv.notify_all();
    }

private:
    void consume()
    {
        while (true) {
            std::unique_lock<std::mutex> lk(_mutex);
            _cv.wait(lk, [&] { return !_products.empty() || _stopped; });
            if (_stopped)
                return;
            while (!_products.empty()) {
                _consumer(std::move(_products.front()));
                _products.pop();
            }
        }
    }

private:
    std::function<void(Product&&)> _consumer;
    std::queue<Product> _products{};
    std::thread _thread{};
    std::mutex _mutex{};
    std::condition_variable _cv{};
    bool _stopped{ false };
};
}

#endif //jm4R_PRODUCER_CONSUMER
