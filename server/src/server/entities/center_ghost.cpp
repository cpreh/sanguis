#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/optional/combine.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::center_ghost::center_ghost() : sanguis::server::entities::center_simple()
{
}

sanguis::server::entities::center_ghost::~center_ghost() = default;

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::center_ghost::on_transfer(
    sanguis::server::entities::transfer_parameters const &_parameters)
{
  return fcppt::optional::combine(
      sanguis::server::entities::center_simple::on_transfer(_parameters),
      sanguis::server::entities::with_ghosts::on_transfer(_parameters),
      [](sanguis::server::entities::transfer_result &&_result1,
         sanguis::server::entities::transfer_result &&_result2) {
        return sanguis::server::entities::combine_transfer(
            std::move(_result1), std::move(_result2));
      });
}
