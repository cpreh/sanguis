#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CREATE_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/create_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/creator/optional_background_tile.hpp>


namespace sanguis::client::draw2d::entities
{

class create_parameters
{
public:
	create_parameters(
		sanguis::client::draw2d::insert_own_callback &&,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::creator::optional_background_tile
	);

	[[nodiscard]]
	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const;

	[[nodiscard]]
	sanguis::client::draw2d::entities::load_parameters const &
	load_parameters() const;

	[[nodiscard]]
	sanguis::creator::optional_background_tile
	background_tile() const;
private:
	sanguis::client::draw2d::insert_own_callback insert_own_callback_;

	sanguis::client::draw2d::entities::load_parameters load_parameters_;

	sanguis::creator::optional_background_tile background_tile_;
};

}

#endif
