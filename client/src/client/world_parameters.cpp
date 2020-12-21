#include <sanguis/world_id.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::world_parameters::world_parameters(
	sanguis::world_id const _world_id,
	sanguis::creator::top_parameters &&_top_parameters
)
:
	world_id_(
		_world_id
	),
	top_parameters_(
		std::move(
			_top_parameters
		)
	)
{
}

sanguis::world_id
sanguis::client::world_parameters::world_id() const
{
	return
		world_id_;
}

sanguis::creator::top_parameters const &
sanguis::client::world_parameters::top_parameters() const
{
	return
		top_parameters_;
}
