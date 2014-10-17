#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/creator/destructible_type_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
destructible(
	sanguis::client::draw2d::entities::load_parameters const &,
	sanguis::creator::destructible_type
);

}
}
}
}

#endif
