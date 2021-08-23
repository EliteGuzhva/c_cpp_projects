#include <iostream>
#include <type_traits>
#include <vector>

class AWidget {};

struct vtable {
  void (*destroy_)(void *ptr);
  void *(*clone_)(void *ptr);
  void *(*move_clone_)(void *ptr);

  // base class methods
  void (*print_)(void *ptr);
};

template <class Concrete>
constexpr vtable vtable_for{
    [](void *ptr) { delete static_cast<Concrete *>(ptr); },
    [](void *ptr) -> void * {
      return new Concrete(*static_cast<Concrete *>(ptr));
    },
    [](void *ptr) -> void * {
      return new Concrete(std::move(*static_cast<Concrete *>(ptr)));
    },

    [](void *ptr) { static_cast<Concrete *>(ptr)->print(); }
};

struct Widget {
  void *concrete_;
  vtable const *vtable_;

  template <class T, typename = std::enable_if_t<std::is_base_of_v<AWidget, T>>>
  Widget(T const &t) : concrete_(new T(t)), vtable_(&vtable_for<T>) {}

  Widget(Widget const &rhs)
      : concrete_(rhs.vtable_->clone_(rhs.concrete_)), vtable_(rhs.vtable_) {}

  Widget(Widget &&rhs)
      : concrete_(rhs.vtable_->move_clone_(rhs.concrete_)),
        vtable_(rhs.vtable_) {}

  Widget &operator=(Widget const &rhs) {
    concrete_ = rhs.vtable_->clone_(rhs.concrete_);
    vtable_ = rhs.vtable_;

    return *this;
  }

  Widget &operator=(Widget &&rhs) {
    concrete_ = rhs.vtable_->move_clone_(rhs.concrete_);
    vtable_ = rhs.vtable_;

    return *this;
  }

  void print() { vtable_->print_(concrete_); }

  ~Widget() { vtable_->destroy_(concrete_); }
};

class Label : private AWidget {
public:
  void print() { std::cout << "Label\n"; }
};

class Button : private AWidget {
public:
  void print() { std::cout << "Button\n"; }
};

int main() {
  Widget l = Label();
  Widget b = Button();

  std::vector widgets = {l, b};
  for (auto &&w : widgets)
    w.print();

  return 0;
}
