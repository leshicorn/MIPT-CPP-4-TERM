#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <stdexcept>

#include "test_runner.h"

using namespace std;

template<typename T>
void AssertEqual(const T& t1, const T& t2, const string& hint = "") {
    if (t1 != t2) {
        cout << "Assertion failed: " << t1 << " != " << t2;
        if (!hint.empty()) {
            cout << " Hint: " << hint;
        }
        cout << endl;
    }
}

#define ASSERT_EQUAL(x, y) AssertEqual(x, y, __FILE__ ":" + to_string(__LINE__))


template <class T>
class ObjectPool {
public:
    ObjectPool() = default;

    T* Allocate() {
        T* object = nullptr;
        if (!free_objects_.empty()) {
            object = free_objects_.front();
            free_objects_.pop();
        } else {
            object = new T;
        }
        allocated_objects_.insert(object);
        return object;
    }

    T* TryAllocate() {
        if (free_objects_.empty()) {
            return nullptr;
        }
        return Allocate();
    }

    void Deallocate(T* object) {
        auto it = allocated_objects_.find(object);
        if (it == allocated_objects_.end()) {
            throw invalid_argument("Object is not allocated by this pool");
        }
        allocated_objects_.erase(it);
        free_objects_.push(object);
    }

    ~ObjectPool() {
        for (auto object : allocated_objects_) {
            delete object;
        }
        while (!free_objects_.empty()) {
            delete free_objects_.front();
            free_objects_.pop();
        }
    }

private:
    set<T*> allocated_objects_;
    queue<T*> free_objects_;
};


void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
