#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/load/model/weapon_pickup_path.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <sanguis/messages/server/add_weapon_pickup.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <alda/message/init_record.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::pickups::weapon::weapon(
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::team const _team,
    sanguis::server::weapons::unique_ptr &&_weapon)
    : sanguis::server::entities::ifaces::with_team(),
      sanguis::server::entities::with_body(
          _load_context.model_size(sanguis::load::model::weapon_pickup_path(_weapon->type())),
          sanguis::server::optional_mass()),
      sanguis::server::entities::with_id(_load_context.next_id()),
      sanguis::server::entities::with_links(),
      team_(_team),
      weapon_(std::move(_weapon))
{
}

sanguis::server::entities::pickups::weapon::~weapon() = default;

sanguis::server::weapons::unique_ptr sanguis::server::entities::pickups::weapon::obtain()
{
  // TODO(philipp): Return an optional_unique_ptr here?
  sanguis::server::weapons::unique_ptr result(std::move(FCPPT_ASSERT_OPTIONAL_ERROR(weapon_)));

  weapon_ = sanguis::server::weapons::optional_unique_ptr();

  return result;
}

sanguis::weapon_type sanguis::server::entities::pickups::weapon::weapon_type() const
{
  return this->get().type();
}

bool sanguis::server::entities::pickups::weapon::dead() const { return !weapon_.has_value(); }

sanguis::server::team sanguis::server::entities::pickups::weapon::team() const { return team_; }

sanguis::collision::world::body_group
sanguis::server::entities::pickups::weapon::collision_group() const
{
  return sanguis::collision::world::body_group::weapon_pickup;
}

sanguis::messages::server::unique_ptr sanguis::server::entities::pickups::weapon::add_message(
    sanguis::server::player_id const, sanguis::collision::world::created const _created) const
{
  sanguis::weapon_description const description(this->get().description());

  return sanguis::messages::server::create_ptr(
      alda::message::init_record<sanguis::messages::server::add_weapon_pickup>(
          sanguis::messages::roles::entity_id{} = this->id(),
          sanguis::messages::roles::center{} = this->center().get(),
          sanguis::messages::roles::angle{} = this->angle().get(),
          sanguis::messages::roles::created{} = _created.get(),
          sanguis::messages::roles::weapon_type{} = description.weapon_type(),
          // TODO(philipp): Unify this with give_weapon
          sanguis::messages::roles::magazine_base_size{} =
              sanguis::messages::convert::to_magazine_size(description.magazine_size().get()),
          sanguis::messages::roles::magazine_extra_size{} =
              sanguis::messages::convert::to_magazine_size(description.magazine_extra().get()),
          sanguis::messages::roles::magazine_remaining{} =
              sanguis::messages::convert::to_magazine_size(description.magazine_remaining().get()),
          sanguis::messages::roles::reload_time{} = description.reload_time().get(),
          sanguis::messages::roles::weapon_attribute_container{} =
              sanguis::messages::convert::to_weapon_attribute_vector(description.attributes())

              ));
}

sanguis::server::weapons::weapon &sanguis::server::entities::pickups::weapon::get() const
{
  return *FCPPT_ASSERT_OPTIONAL_ERROR(weapon_);
}
