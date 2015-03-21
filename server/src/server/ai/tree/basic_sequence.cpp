#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::tree::basic_sequence::basic_sequence(
	sanguis::server::ai::tree::container &&_children
)
:
	sanguis::server::ai::tree::base(),
	children_(
		std::move(
			_children
		)
	)
{
}

sanguis::server::ai::tree::basic_sequence::~basic_sequence()
{
}

sanguis::server::entities::transfer_result
sanguis::server::ai::tree::basic_sequence::transfer()
{
	return
		fcppt::algorithm::fold(
			children_,
			sanguis::server::entities::transfer_result(),
			[](
				sanguis::server::ai::tree::base_unique_ptr const &_child,
				sanguis::server::entities::transfer_result &&_state
			)
			{
				return
					sanguis::server::entities::combine_transfer(
						_child->transfer(),
						std::move(
							_state
						)
					);
			}
		);
}

sanguis::server::ai::tree::container &
sanguis::server::ai::tree::basic_sequence::get()
{
	return
		children_;
}
