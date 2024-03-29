#ifndef SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED

#include <sanguis/random_generator_ref.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/object_ref.hpp>
#include <sanguis/server/random/distributor_decl.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/type_iso/strong_typedef.hpp> // IWYU pragma: keep

namespace sanguis::server::world
{

class pickup_spawner
{
  FCPPT_NONMOVABLE(pickup_spawner);

public:
  pickup_spawner(
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &,
      sanguis::server::environment::object_ref);

  ~pickup_spawner();

  void spawn(
      sanguis::server::pickup_probability,
      sanguis::server::center const &,
      sanguis::server::entities::enemies::difficulty);

private:
  void
  spawn_health(sanguis::server::center const &, sanguis::server::entities::enemies::difficulty);

  void spawn_weapon(
      sanguis::server::center const &,
      sanguis::server::entities::enemies::difficulty,
      sanguis::weapon_type);

  void
  spawn_entity(sanguis::server::entities::with_id_unique_ptr &&, sanguis::server::center const &);

  using spawn_function = fcppt::function<void(
      sanguis::server::center, sanguis::server::entities::enemies::difficulty)>;

  [[nodiscard]] sanguis::server::world::pickup_spawner::spawn_function
  make_spawn_weapon(sanguis::weapon_type const &);

  sanguis::random_generator_ref const random_generator_;

  sanguis::server::weapons::common_parameters const weapon_parameters_;

  sanguis::server::environment::object_ref const env_;

  using real_distribution =
      fcppt::random::distribution::basic<fcppt::random::distribution::parameters::uniform_real<
          sanguis::server::pickup_probability::value_type>>;

  using distributor =
      sanguis::server::random::distributor<sanguis::server::pickup_probability, spawn_function>;

  distributor distributor_;

  real_distribution spawn_prob_;
};

}

#endif
