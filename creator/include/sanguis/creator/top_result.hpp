#ifndef SANGUIS_CREATOR_TOP_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_TOP_RESULT_HPP_INCLUDED

#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/top_result_fwd.hpp> // IWYU pragma: keep

namespace sanguis::creator
{

class top_result
{
public:
  top_result(
      sanguis::creator::seed,
      sanguis::creator::name &&,
      sanguis::creator::spawn_boss,
      sanguis::creator::grid &&,
      sanguis::creator::background_grid &&,
      sanguis::creator::opening_container_array &&,
      sanguis::creator::spawn_container &&,
      sanguis::creator::destructible_container &&);

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::seed seed() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::name const &name() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::spawn_boss spawn_boss() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::grid const &grid() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::background_grid const &
  background_grid() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::opening_container_array const &
  openings() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::spawn_container const &spawns() const;

  [[nodiscard]] SANGUIS_CREATOR_SYMBOL sanguis::creator::destructible_container const &
  destructibles() const;

private:
  sanguis::creator::seed seed_;

  sanguis::creator::name name_;

  sanguis::creator::spawn_boss spawn_boss_;

  sanguis::creator::grid grid_;

  sanguis::creator::background_grid background_grid_;

  sanguis::creator::opening_container_array openings_;

  sanguis::creator::spawn_container spawns_;

  sanguis::creator::destructible_container destructibles_;
};

}

#endif
