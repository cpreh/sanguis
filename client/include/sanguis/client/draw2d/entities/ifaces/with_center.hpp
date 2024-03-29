#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_CENTER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_CENTER_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/center.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities::ifaces
{

class with_center
{
  FCPPT_NONMOVABLE(with_center);

protected:
  with_center();

public:
  virtual ~with_center();

  virtual void center(sanguis::client::draw2d::sprite::center const &) = 0;
};

}

#endif
