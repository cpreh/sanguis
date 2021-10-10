#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::server::entities::enemies::factory
{

class parameters
{
public:
  parameters(
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &,
      sanguis::creator::enemy_type,
      sanguis::creator::enemy_kind,
      sanguis::server::entities::enemies::difficulty,
      sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
      sanguis::server::entities::spawn_owner,
      sanguis::server::entities::enemies::special_chance);

  [[nodiscard]] sanguis::random_generator &random_generator() const;

  [[nodiscard]] sanguis::server::weapons::common_parameters const &weapon_parameters() const;

  [[nodiscard]] sanguis::creator::enemy_type enemy_type() const;

  [[nodiscard]] sanguis::creator::enemy_kind enemy_kind() const;

  [[nodiscard]] sanguis::server::entities::enemies::difficulty difficulty() const;

  [[nodiscard]] sanguis::server::environment::load_context &load_context() const;

  [[nodiscard]] sanguis::server::entities::spawn_owner const &spawn_owner() const;

  [[nodiscard]] sanguis::server::entities::enemies::special_chance special_chance() const;

private:
  sanguis::random_generator_ref random_generator_;

  sanguis::server::weapons::common_parameters weapon_parameters_;

  sanguis::creator::enemy_type enemy_type_;

  sanguis::creator::enemy_kind enemy_kind_;

  sanguis::server::entities::enemies::difficulty difficulty_;

  fcppt::reference<sanguis::server::environment::load_context> load_context_;

  sanguis::server::entities::spawn_owner spawn_owner_;

  sanguis::server::entities::enemies::special_chance special_chance_;
};

}

#endif
