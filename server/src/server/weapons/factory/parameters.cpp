#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>

sanguis::server::weapons::factory::parameters::parameters(
    sanguis::server::weapons::common_parameters const &_common_parameters,
    sanguis::weapon_type const _weapon_type,
    sanguis::server::entities::enemies::difficulty const _difficulty)
    : common_parameters_{_common_parameters}, weapon_type_(_weapon_type), difficulty_(_difficulty)
{
}

sanguis::server::weapons::common_parameters const &
sanguis::server::weapons::factory::parameters::common_parameters() const
{
  return common_parameters_;
}

sanguis::random_generator &sanguis::server::weapons::factory::parameters::random_generator() const
{
  return this->common_parameters().random_generator();
}

sanguis::weapon_type sanguis::server::weapons::factory::parameters::weapon_type() const
{
  return weapon_type_;
}

sanguis::server::entities::enemies::difficulty
sanguis::server::weapons::factory::parameters::difficulty() const
{
  return difficulty_;
}
