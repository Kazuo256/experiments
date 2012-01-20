
#ifndef VEC2_H_
#define VEC2_H_

namespace base {

class vec2 {
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

}

#endif

