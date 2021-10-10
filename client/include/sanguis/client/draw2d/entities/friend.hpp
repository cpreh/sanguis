#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_FRIEND_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities
{

class friend_ : public sanguis::client::draw2d::entities::with_buffs_auras_model
{
  FCPPT_NONMOVABLE(friend_);

public:
  friend_(
      sanguis::client::draw2d::entities::load_parameters const &,
      sanguis::client::load::auras::context_ref,
      sanguis::friend_type,
      sanguis::optional_primary_weapon_type,
      sanguis::weapon_status,
      sanguis::client::draw2d::speed const &,
      sanguis::client::draw2d::sprite::center const &,
      sanguis::client::draw2d::sprite::rotation,
      sanguis::aura_type_vector &&,
      sanguis::buff_type_vector &&,
      sanguis::client::draw2d::entities::order_function &&,
      sanguis::client::health_pair);

  ~friend_() override;

private:
  [[nodiscard]] sanguis::client::draw2d::entities::hover::optional_info hover() const override;
};

}

#endif
