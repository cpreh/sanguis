#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/model/destructible_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/destructible_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/server/add_destructible.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/destructible.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <alda/message/init_record.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>

sanguis::server::entities::destructible::destructible(
    sanguis::creator::destructible_type const _type,
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::health const _health,
    sanguis::server::damage::armor_array const &_armor,
    sanguis::server::entities::enemies::difficulty const _difficulty)
    : sanguis::server::entities::with_body(
          _load_context.model_size(sanguis::load::model::destructible_path(_type)),
          sanguis::server::optional_mass()),
      sanguis::server::entities::with_id(_load_context.next_id()),
      sanguis::server::entities::with_health(_health, sanguis::server::regeneration(0.F), _armor),
      sanguis::server::entities::with_links(),
      type_(_type),
      difficulty_(_difficulty)
{
}

sanguis::server::entities::destructible::~destructible() = default;

void sanguis::server::entities::destructible::update()
{
  sanguis::server::entities::with_body::update();

  sanguis::server::entities::with_health::update();
}

void sanguis::server::entities::destructible::remove_from_game()
{
  fcppt::optional::maybe_void(
      this->environment(),
      [this](fcppt::reference<sanguis::server::environment::object> const _environment)
      {
        _environment.get().pickup_chance(
            sanguis::server::pickup_probability(
                0.1F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                ),
            difficulty_,
            this->center());
      });
}

sanguis::server::team sanguis::server::entities::destructible::team() const
{
  return sanguis::server::team::monsters;
}

sanguis::collision::world::body_group
sanguis::server::entities::destructible::collision_group() const
{
  return sanguis::collision::world::body_group::destructible;
}

sanguis::messages::server::unique_ptr sanguis::server::entities::destructible::add_message(
    sanguis::server::player_id const, sanguis::collision::world::created const _created) const
{
  return sanguis::messages::server::create_ptr(
      alda::message::init_record<sanguis::messages::server::add_destructible>(
          sanguis::messages::roles::entity_id{} = this->id(),
          sanguis::messages::roles::center{} = this->center().get(),
          sanguis::messages::roles::angle{} = this->angle().get(),
          sanguis::messages::roles::created{} = _created.get(),
          sanguis::messages::roles::destructible_type{} = type_));
}
