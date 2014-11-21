#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/scene/world/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/create.hpp>
#include <sanguis/client/draw2d/scene/world/graveyard.hpp>
#include <sanguis/client/draw2d/scene/world/none.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/creator/name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sanguis::client::draw2d::scene::world::base_unique_ptr
sanguis::client::draw2d::scene::world::create(
	sanguis::creator::name const &_name,
	sanguis::client::draw2d::scene::world::parameters const &_parameters
)
{
	if(
		_name.get()
		==
		FCPPT_TEXT("graveyard")
	)
		return
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::scene::world::graveyard
			>(
				_parameters.load_context(),
				_parameters.client_system(),
				_parameters.viewport_manager()
			);

	FCPPT_LOG_ERROR(
		sanguis::client::draw2d::log(),
		fcppt::log::_
			<< FCPPT_TEXT("World ")
			<< _name
			<< FCPPT_TEXT(" not implemented.")
	);

	return
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::world::none
		>();
}
