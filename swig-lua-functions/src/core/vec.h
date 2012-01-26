
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

#ifdef SWIG
register_class(vec2)
#endif
}

#ifdef SWIG
register_class(rect)
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

