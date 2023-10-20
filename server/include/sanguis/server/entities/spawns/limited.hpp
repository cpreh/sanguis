#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/entities/spawns/total_count.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::spawns
{

class limited : public sanguis::server::entities::spawns::spawn
{
  FCPPT_NONMOVABLE(limited);

public:
  limited(
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &,
      sanguis::creator::enemy_type,
      sanguis::creator::enemy_kind,
      sanguis::server::world::difficulty,
      sanguis::server::entities::spawns::count_per_wave,
      sanguis::server::entities::spawns::interval,
      sanguis::server::entities::spawns::limit,
      sanguis::server::entities::spawns::total_count);

  ~limited() override;

private:
  [[nodiscard]] bool dead() const override;

  void unregister(sanguis::server::entities::base &) override; // NOLINT(google-runtime-references)

  [[nodiscard]] sanguis::server::entities::spawns::size_type may_spawn() override;

  void add_count(sanguis::server::entities::spawns::size_type) override;

  sanguis::server::entities::spawns::count_per_wave const count_per_wave_;

  sanguis::diff_timer delay_timer_;

  sanguis::server::entities::spawns::size_type alive_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sanguis::server::entities::spawns::size_type spawned_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sanguis::server::entities::spawns::limit const limit_;

  sanguis::server::entities::spawns::total_count const total_count_;
};

}

#endif
