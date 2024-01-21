#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp> // IWYU pragma: keep

void sanguis::server::perks::perk::update(
    sanguis::server::entities::with_perks &, sanguis::server::environment::object &)
{
}

void sanguis::server::perks::perk::raise_level(sanguis::server::entities::with_perks &_owner)
{
  this->change(_owner, sanguis::server::perks::level_diff(1));

  ++level_;
}

sanguis::perk_type sanguis::server::perks::perk::type() const { return type_; }

sanguis::server::perks::perk::~perk() = default;

sanguis::server::perks::perk::perk(sanguis::perk_type const _type) : type_(_type), level_(0U) {}

sanguis::server::level sanguis::server::perks::perk::level() const { return level_; }
