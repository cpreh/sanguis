#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/server/direction_fwd.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::ifaces
{

class with_velocity
{
  FCPPT_NONMOVABLE(with_velocity);

protected:
  with_velocity();

public:
  [[nodiscard]] virtual sanguis::server::speed speed() const = 0;

  [[nodiscard]] virtual sanguis::server::entities::property::changeable &movement_speed() = 0;

  virtual void direction(sanguis::server::direction) = 0;

  virtual ~with_velocity();
};

}

#endif
