
#include <cstdlib>
#include <cstdio>

#include <string>

#include <unordered_map>
#include <type_traits>

using std::string;
using std::tr1::unordered_map;

class vec2f {
  public:
    vec2f(float x, float y) :
        x_(x), y_(y) {}
    float x() const { return x_; }
    float y() const { return y_; }
    void set_x(const float x) { x_ = x; }
    void set_y(const float y) { y_ = y; }
  private:
    float x_,y_;
};

template <class T>
T
parse (string text) { return T(); }

template <>
int
parse<int> (string text) { return atoi(text.c_str()); }

template <class T>
class method_traits {};

template <class T, class Tret, class Targ1>
class method_traits<Tret (T::*) (Targ1)> {
    typedef T       class_type;
    typedef Tret    result_type;
    typedef Targ1   arg1_type;
};

class Loader {
  public:
    virtual ~Loader() {}

    virtual void
    load (string arg) = 0;
  protected:
    Loader() {}
};


template <class T, class Ftraits>
class DefaultLoader : public Loader {
  public:

    typedef typename Ftraits::result_type   result_type;
    typedef typename Ftraits::arg1_type     arg1_type;
    typedef result_type                     (*method_type) (arg1_type);

    DefaultLoader(T& obj, method_type method) : obj_(obj), method_(method) {}
    ~DefaultLoader() {}

    void
    load (string arg) {
        arg1_type arg_value = parse<arg1_type>(arg);
        obj_.*method_(arg_value);
    }
  private:
    T& obj_;
    result_type (T::*method_) (arg1_type);
};

template <class T>
class VirtualClass {
  public:
    template <typename Tret, typename Targ1>
    void RegisterMethod(string method_name, Tret (T::*method_ptr) (Targ1)) {
        methods_[method_name] = DefaultLoader<T,method_traits<Tret (T::*) (Targ1)> >(T(), method_ptr);
    }
  private:
    unordered_map<string, Loader&> methods_;
};



int main () {

    string number = "10";
    int x = parse<int>(number);

    printf("%d\n", x);

    return 0;
}

