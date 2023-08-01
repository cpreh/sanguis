#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities::ifaces
{

class with_health
{
  FCPPT_NONMOVABLE(with_health);

protected:
  with_health();

public:
  virtual ~with_health();

  virtual void health(sanguis::client::health) = 0;

  virtual void max_health(sanguis::client::max_health) = 0;
};

}

#endif
