#include <sanguis/server/entities/combine_remove_from_world.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <fcppt/container/join.hpp>

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::combine_remove_from_world(
    sanguis::server::entities::remove_from_world_result &&_left, // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
    sanguis::server::entities::remove_from_world_result &&_right) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
{
  return sanguis::server::entities::remove_from_world_result(
      fcppt::container::join(_left.release_body_exit(), _right.release_body_exit()));
}
