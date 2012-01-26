
#include <core/vec.h>

namespace base {

vec2 vec2::add (const vec2& rhs) {
  this->x_ += rhs.x();
  this->y_ += rhs.y();
}

}

