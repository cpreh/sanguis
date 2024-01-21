#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SENTRY_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities
{

class sentry : public sanguis::client::draw2d::entities::friend_
{
  FCPPT_NONMOVABLE(sentry);

public:
  sentry(
      sanguis::client::draw2d::entities::load_parameters const &,
      sanguis::client::load::auras::context_ref,
      sanguis::optional_primary_weapon_type,
      sanguis::weapon_status,
      sanguis::client::draw2d::speed const &,
      sanguis::client::draw2d::sprite::center const &,
      sanguis::client::draw2d::sprite::rotation,
      sanguis::aura_type_vector &&,
      sanguis::buff_type_vector &&,
      sanguis::client::health_pair);

  ~sentry() override;

  void orientation(sanguis::client::draw2d::sprite::rotation) override;

private:
  using sanguis::client::draw2d::entities::container::orientation;
};

}

#endif
