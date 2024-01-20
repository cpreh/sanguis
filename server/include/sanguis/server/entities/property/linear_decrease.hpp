#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECREASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_DECREASE_HPP_INCLUDED

#include <sanguis/server/entities/property/linear_decrease_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/entities/property/value.hpp>

namespace sanguis::server::entities::property
{

class linear_decrease
{
public:
  linear_decrease();

  void mul(sanguis::server::entities::property::value);

  void div(sanguis::server::entities::property::value);

  [[nodiscard]] sanguis::server::entities::property::value value() const;

private:
  sanguis::server::entities::property::value value_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
