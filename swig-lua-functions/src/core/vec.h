
#ifndef VEC2_H_
#define VEC2_H_

namespace swig {
  
template <typename T> class woot {};

}

#ifdef SWIG
%define swig_class(classname)
  class classname;
  %template(woot_##classname) swig::woot<classname>;
  class classname
%enddef
#else
#define swig_class(classname) class classname
#endif

namespace base {

swig_class(vec2) {
  public:
    vec2 (float x = 0.0f, float y = 0.0f) :
      x_(x), y_(y) {}
    float x () const { return x_; }
    float y () const { return y_; }
    void set_x (const float x) { x_ = x; }
    void set_y (const float y) { y_ = y; }
    vec2 add (const vec2& rhs);
  private:
    float x_, y_;
};

typedef vec2 (*binop_t) (const vec2&, const vec2&);

void exec_binop(binop_t binop, const vec2& lhs, const vec2& rhs);

}

//DECLARE_CLASS(rect)

#ifndef SWIG
# undef swig_class
#endif

class rect {
  public:
    rect (const base::vec2& pos, const base::vec2& dim) :
      pos_(pos), dim_(dim) {}
    rect (const float x, const float y, const float w, const float h) :
      pos_(x, y), dim_(w, h) {}
    base::vec2 pos() const { return pos_; }
    base::vec2 dim() const { return dim_; }
    void set_pos(const base::vec2& pos) { pos_ = pos; }
    void set_dim(const base::vec2& dim) { dim_ = dim; }
  private:
    base::vec2 pos_, dim_;
};

#endif

