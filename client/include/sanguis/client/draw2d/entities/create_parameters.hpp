#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CREATE_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/create_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/creator/optional_background_tile.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class create_parameters
{
	FCPPT_NONASSIGNABLE(
		create_parameters
	);
public:
	create_parameters(
		sanguis::client::draw2d::insert_own_callback const &,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::creator::optional_background_tile
	);

	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const;

	sanguis::client::draw2d::entities::load_parameters const &
	load_parameters() const;

	sanguis::creator::optional_background_tile const
	background_tile() const;
private:
	sanguis::client::draw2d::insert_own_callback const insert_own_callback_;

	sanguis::client::draw2d::entities::load_parameters const &load_parameters_;

	sanguis::creator::optional_background_tile const background_tile_;
};

}
}
}
}

#endif
