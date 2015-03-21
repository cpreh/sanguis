#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/algorithm/join_move.hpp>


sanguis::server::entities::transfer_result
sanguis::server::entities::combine_transfer(
	sanguis::server::entities::transfer_result &&_left,
	sanguis::server::entities::transfer_result &&_right
)
{
	return
		sanguis::server::entities::transfer_result(
			fcppt::algorithm::join_move(
				_left.release_body_enter(),
				_right.release_body_enter()
			)
		);
}
