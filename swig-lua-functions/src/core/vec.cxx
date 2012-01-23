
#include <core/vec.h>

namespace base {

vec2 vec2::add (const vec2& rhs) {
  this->x_ += rhs.x();
  this->y_ += rhs.y();
}

void exec_binop(binop_t binop, const vec2& lhs, const vec2& rhs) {
  (*binop) (lhs, rhs);
}

}

