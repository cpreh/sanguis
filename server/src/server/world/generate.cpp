#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/top_parameters_fwd.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::world::object_unique_ptr sanguis::server::world::generate(
    sanguis::server::world::parameters const &_parameters,
    sanguis::world_id const _world_id,
    sanguis::world_name &&_world_name,
    sanguis::server::world::difficulty const _difficulty,
    sanguis::creator::top_parameters const &_top_parameters)
{
  return fcppt::make_unique_ptr<sanguis::server::world::object>(
      _parameters,
      _world_id,
      sanguis::creator::generate(_top_parameters),
      _difficulty,
      std::move(_world_name));
}
