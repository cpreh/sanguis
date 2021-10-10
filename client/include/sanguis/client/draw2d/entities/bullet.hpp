#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BULLET_HPP_INCLUDED

#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities
{

class bullet : public sanguis::client::draw2d::entities::model::object
{
  FCPPT_NONMOVABLE(bullet);

public:
  bullet(
      sanguis::client::draw2d::entities::load_parameters const &,
      sanguis::client::draw2d::speed const &,
      sanguis::client::draw2d::sprite::center const &,
      sanguis::client::draw2d::sprite::rotation,
      sanguis::load::model::path &&);

  ~bullet() override;

private:
  void update() override;

  sanguis::client::draw2d::sprite::center const origin_;
};

}

#endif
