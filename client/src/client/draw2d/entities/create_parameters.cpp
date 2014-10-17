#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/create_parameters.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/creator/optional_background_tile.hpp>


sanguis::client::draw2d::entities::create_parameters::create_parameters(
	sanguis::client::draw2d::insert_own_callback const &_insert_own_callback,
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::creator::optional_background_tile const _background_tile
)
:
	insert_own_callback_{
		_insert_own_callback
	},
	load_parameters_(
		_load_parameters
	),
	background_tile_{
		_background_tile
	}
{
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::entities::create_parameters::insert_own_callback() const
{
	return
		insert_own_callback_;
}

sanguis::client::draw2d::entities::load_parameters const &
sanguis::client::draw2d::entities::create_parameters::load_parameters() const
{
	return
		load_parameters_;
}

sanguis::creator::optional_background_tile const
sanguis::client::draw2d::entities::create_parameters::background_tile() const
{
	return
		background_tile_;
}
