#ifndef SANGUIS_COLLISION_RESULT_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/symbol.hpp>

namespace sanguis::collision
{

class result
{
public:
  explicit result(sanguis::collision::speed);

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::speed speed() const;

private:
  sanguis::collision::speed speed_;
};

}

#endif
