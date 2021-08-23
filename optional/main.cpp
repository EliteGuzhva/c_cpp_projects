#include <ios>
#include <iostream>
#include <string>

struct Person {
  std::string name;
  int age;

  Person() {
    std::cout << "Alive\n";
  }

  Person(const std::string& name, int age) {
    this->name = name;
    this->age = age;

    std::cout << "Alive\n";
  }

  ~Person() {
    std::cout << "Dead\n";
  }
};


struct NullOpt {
};

NullOpt nullopt;


template<typename T>
class Optional {
public:
  Optional() {
    new (m_buffer) T();
    m_empty = true;
  }

  Optional(T&& obj) {
    new (m_buffer) T(std::move(obj));
    m_empty = false;
    std::cout << "Move" << std::endl;
  }

  Optional(const T& obj) {
    new (m_buffer) T(obj);
    m_empty = false;
    std::cout << "Copy" << std::endl;
  }

  void operator=(T&& obj) {
    new (m_buffer) T(std::move(obj));
    m_empty = false;
    std::cout << "Move=" << std::endl;
  }

  void operator=(const T& obj) {
    new (m_buffer) T(obj);
    m_empty = false;
    std::cout << "Copy=" << std::endl;
  }

  friend bool operator== (const Optional &lhs, const NullOpt &rhs) {
    return lhs.m_empty;
  }

  friend bool operator== (const NullOpt &lhs, const Optional &rhs) {
    return rhs.m_empty;
  }

  T& get() {
    return *m_buffer;
  }

  ~Optional() {
    m_buffer->~T();

    operator delete(m_buffer);
  }

private:
  T* m_buffer = static_cast<T*>(operator new(sizeof(T)));
  bool m_empty = true;
};


int main() {
  Optional<Person> p;
  p = Person{"Nikita", 22};

  std::cout << std::boolalpha << (p == nullopt) << std::endl;

  return 0;
}
