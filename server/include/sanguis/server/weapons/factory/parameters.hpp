#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp> // IWYU pragma: keep

namespace sanguis::server::weapons::factory
{

class parameters
{
public:
  parameters(
      sanguis::server::weapons::common_parameters const &,
      sanguis::weapon_type,
      sanguis::server::entities::enemies::difficulty);

  [[nodiscard]] sanguis::server::weapons::common_parameters const &common_parameters() const;

  [[nodiscard]] sanguis::random_generator &random_generator() const;

  [[nodiscard]] sanguis::weapon_type weapon_type() const;

  [[nodiscard]] sanguis::server::entities::enemies::difficulty difficulty() const;

private:
  sanguis::server::weapons::common_parameters common_parameters_;

  sanguis::weapon_type weapon_type_;

  sanguis::server::entities::enemies::difficulty difficulty_;
};

}

#endif
