#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/container/join.hpp>

sanguis::server::entities::transfer_result sanguis::server::entities::combine_transfer(
    sanguis::server::entities::transfer_result &&_left, // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
    sanguis::server::entities::transfer_result &&_right) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
{
  return sanguis::server::entities::transfer_result(
      fcppt::container::join(_left.release_body_enter(), _right.release_body_enter()));
}
