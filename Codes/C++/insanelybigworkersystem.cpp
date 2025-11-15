
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>
#include <optional>
#include <vector>
#include <queue>

constexpr size_t MAX_BUF = 0xF;
constexpr size_t MAX_WORKERS = 0x14;
constexpr uint32_t MAX_WAIT = 0x124F8;

enum class Line {
    LINE_1,
    LINE_2,
    NULL_L
};

class Worker {
private:
    uint64_t id;
    std::string nome;
    Line l;
    uint32_t prod;

public:
    Worker();
    ~Worker() = default;

    Worker(const Worker&) = default;
    Worker(Worker&&) = default;
    Worker& operator=(const Worker&) = default;
    Worker& operator=(Worker&&) = default;

    void setLine(Line ln);
    void setProd(uint32_t p);

    uint64_t getId() const;
    const std::string& getNome() const;
    Line getLine() const;
    uint32_t getProd() const;
};

class WorkerQueue {
private:
    std::queue<std::shared_ptr<Worker>> workers;

public:
    WorkerQueue() = default;
    ~WorkerQueue() = default;

    void push(std::shared_ptr<Worker> w);
    std::optional<std::shared_ptr<Worker>> pop();
    size_t size() const;
    void clear();
};

template<typename T>
class MemPool {
private:
    std::vector<std::unique_ptr<T>> pool;
    size_t capacity;

public:
    explicit MemPool(size_t cap) : capacity(cap) {
        pool.reserve(cap);
    }

    ~MemPool() = default;

    MemPool(const MemPool&) = delete;
    MemPool& operator=(const MemPool&) = delete;
    MemPool(MemPool&&) = default;
    MemPool& operator=(MemPool&&) = default;

    template<typename... Args>
    T* alloc(Args&&... args);

    void reset();
    size_t size() const;
    size_t getCapacity() const;
};

std::string& trim(std::string& str);
void wait_ms(uint32_t tm);
void clear_screen();
