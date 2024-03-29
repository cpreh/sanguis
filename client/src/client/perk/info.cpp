#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/max_level.hpp>
#include <sanguis/client/perk/required_parent_level.hpp>
#include <sanguis/client/perk/required_player_level.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp> // IWYU pragma: keep

sanguis::client::perk::info::info(sanguis::perk_type const _type)
    : type_(_type),
      level_(sanguis::client::level(0U)),
      required_parent_level_(sanguis::client::perk::level(sanguis::client::level(0U))),
      required_player_level_(sanguis::client::player_level(sanguis::client::level(0U))),
      max_level_(sanguis::client::perk::level(sanguis::client::level(0U)))
{
}

sanguis::client::perk::info::info(
    sanguis::perk_type const _type,
    sanguis::client::perk::level const _level,
    sanguis::client::perk::required_parent_level const _required_parent_level,
    sanguis::client::perk::required_player_level const _required_player_level,
    sanguis::client::perk::max_level const _max_level)
    : type_(_type),
      level_(_level),
      required_parent_level_(_required_parent_level),
      required_player_level_(_required_player_level),
      max_level_(_max_level)
{
}

void sanguis::client::perk::info::increment_level() { ++level_; }

sanguis::perk_type sanguis::client::perk::info::perk_type() const { return type_; }

sanguis::client::perk::level sanguis::client::perk::info::level() const { return level_; }

sanguis::client::perk::required_parent_level
sanguis::client::perk::info::required_parent_level() const
{
  return required_parent_level_;
}

sanguis::client::perk::required_player_level
sanguis::client::perk::info::required_player_level() const
{
  return required_player_level_;
}

sanguis::client::perk::max_level sanguis::client::perk::info::max_level() const
{
  return max_level_;
}
