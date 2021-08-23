#include <cstddef>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

template <typename T> struct RawMemory {
  T *buf = nullptr;
  size_t cp = 0;

  static T *allocate(size_t n = 1) {
    return static_cast<T *>(operator new(n * sizeof(T)));
  }

  static void deallocate(T *buf) { operator delete(buf); }

  RawMemory() = default;

  RawMemory(size_t n) {
    buf = allocate(n);
    cp = n;
  }

  RawMemory(const RawMemory &) = delete;

  RawMemory(RawMemory &&other) noexcept { swap(other); }

  RawMemory &operator=(const RawMemory &) = delete;

  RawMemory &operator=(RawMemory &&other) {
    swap(other);

    return *this;
  }

  ~RawMemory() { deallocate(buf); }

  T *operator+(size_t i) { return buf + i; }

  const T *operator+(size_t i) const { return buf + i; }

  T &operator[](size_t i) { return buf[i]; }

  const T &operator[](size_t i) const { return buf[i]; }

  void swap(RawMemory &other) noexcept {
    std::swap(buf, other.buf);
    std::swap(cp, other.cp);
  }
};

template <typename T> class Vector {
private:
  RawMemory<T> data;
  size_t sz = 0;

  static void construct(void *buf) { new (buf) T(); }

  static void construct(void *buf, const T &elem) { new (buf) T(elem); }

  static void construct(void *buf, const T &&elem) {
    new (buf) T(std::move(elem));
  }

  static void destroy(T *buf) { buf->~T(); }

public:
  size_t size() const { return sz; }

  size_t capacity() const { return data.cp; }

  const T &operator[](size_t i) const { return data[i]; }

  T &operator[](size_t i) { return data[i]; }

  //! @brief default constructor
  Vector() = default;

  //! @brief constructor
  explicit Vector(size_t n) : data(n) {
    std::uninitialized_value_construct_n(data.buf, n);

    sz = n;
  }

  //! @brief copy constructor
  Vector(const Vector &other) : data(other.sz) {
    size_t n = other.size();

    std::uninitialized_copy_n(other.data.buf, n, data.buf);

    sz = n;
  }

  //! @brief move constructor
  Vector(Vector &&other) noexcept { swap(other); }

  //! @brief move =
  Vector &operator=(Vector &&other) noexcept {
    swap(other);

    return *this;
  }

  //! @brief copy =
  Vector &operator=(const Vector &other) {
    if (other.sz > data.cp) {
      Vector tmp(other);
      swap(tmp);
    } else {
      for (size_t i = 0; i < sz && i < other.sz; i++) {
        data[i] = other[i];
      }
      if (sz < other.sz) {
        std::uninitialized_copy_n(other.data.buf + sz, other.sz - sz,
                                  data.buf + sz);
      } else if (sz > other.sz) {
        std::destroy_n(data.buf + other.sz, sz - other.sz);
      }
      sz = other.sz;
    }

    return *this;
  }

  //! @brief destructor
  ~Vector() {
    for (size_t i = 0; i != sz; i++) {
      destroy(data + i);
    }
  }

  //! @brief swap vectors
  void swap(Vector &other) noexcept {
    data.swap(other.data);
    std::swap(sz, other.sz);
  }

  //! @brief reserve capacity
  void reserve(size_t n) {
    if (n > data.cp) {
      RawMemory<T> data2(n);
      std::uninitialized_move_n(data.buf, sz, data2.buf);
      std::destroy_n(data.buf, sz);
      data.swap(data2);
    }
  }

  //! @brief resize
  void resize(size_t n) {
    reserve(n);

    if (sz < n) {
      std::uninitialized_value_construct_n(data + sz, n - sz);
    } else if (sz > n) {
      std::destroy_n(data + n, sz - n);
    }
    sz = n;
  }

  void push_back(const T &elem) {
    if (sz == data.cp) {
      reserve(sz == 0 ? 1 : sz * 2);
    }

    new (data + sz) T(elem);
    sz++;
  }

  void push_back(T &&elem) {
    if (sz == data.cp) {
      reserve(sz == 0 ? 1 : sz * 2);
    }

    new (data + sz) T(std::move(elem));
    sz++;
  }

  void pop_back() {
    std::destroy_at(data + sz - 1);
    sz--;
  }

  template <typename... Args>
  T& emplace_back(Args&&... args) {
    if (sz == data.cp) {
      reserve(sz == 0 ? 1 : sz * 2);
    }

    auto elem = new (data + sz) T(std::forward<Args>(args)...);
    sz++;

    return *elem;
  }
};

class Test {
public:
  int a = 3;

  Test() = default;
  Test(int value) : a(value) {}
};

int main() {
  Vector<int> v(10);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Size: " << v.size() << std::endl;
  std::cout << "Capacity: " << v.capacity() << std::endl;

  v.resize(2);
  v.push_back(7);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Size: " << v.size() << std::endl;
  std::cout << "Capacity: " << v.capacity() << std::endl;

  v.reserve(20);
  std::cout << "-------------------------" << std::endl;
  std::cout << "Size: " << v.size() << std::endl;
  std::cout << "Capacity: " << v.capacity() << std::endl;

  std::cout << std::endl;
  // ----------------------------------------------------
  Vector<Test> vt;
  vt.push_back(Test(7));
  auto& t = vt.emplace_back(5);

  std::cout << vt[0].a << ", " << vt[1].a << std::endl;
  std::cout << &t << ", " << &vt[1] << std::endl;

  Test t2;
  vt.emplace_back(std::move(t2));

  return 0;
}
