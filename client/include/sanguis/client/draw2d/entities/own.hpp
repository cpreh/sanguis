#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities
{

class own
{
  FCPPT_NONMOVABLE(own);

protected:
  own();

public:
  virtual void update() = 0;

  [[nodiscard]] virtual bool may_be_removed() const = 0;

  virtual ~own() = 0;

  virtual void pause(bool);
};

}

#endif
