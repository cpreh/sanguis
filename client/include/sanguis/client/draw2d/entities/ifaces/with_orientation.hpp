#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities::ifaces
{

class with_orientation
{
  FCPPT_NONMOVABLE(with_orientation);

protected:
  with_orientation();

public:
  virtual ~with_orientation();

  virtual void orientation(sanguis::client::draw2d::sprite::rotation) = 0;

  [[nodiscard]] virtual sanguis::client::draw2d::sprite::rotation orientation() const = 0;
};

}

#endif
