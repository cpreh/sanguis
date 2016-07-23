#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/create.hpp>
#include <sanguis/client/draw2d/scene/world/graveyard.hpp>
#include <sanguis/client/draw2d/scene/world/none.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/creator/name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>


sanguis::client::draw2d::scene::world::base_unique_ptr
sanguis::client::draw2d::scene::world::create(
	fcppt::log::object &_log,
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
			fcppt::unique_ptr_to_base<
				sanguis::client::draw2d::scene::world::base
			>(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::scene::world::graveyard
				>(
					_parameters.load_context(),
					_parameters.client_system(),
					_parameters.viewport_manager()
				)
			);
	if(
		_name.get()
		==
		FCPPT_TEXT("start_area")
	)
		return
			fcppt::unique_ptr_to_base<
				sanguis::client::draw2d::scene::world::base
			>(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::scene::world::none
				>()
			);

	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::_
			<< FCPPT_TEXT("World ")
			<< _name
			<< FCPPT_TEXT(" not implemented.")
	);

	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::scene::world::base
		>(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::scene::world::none
			>()
		);
}
