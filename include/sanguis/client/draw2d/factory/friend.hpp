#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_FRIEND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_FRIEND_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
friend_(
	sanguis::client::draw2d::entities::model::load_parameters const &,
	sanguis::load::auras::context &,
	sanguis::friend_type,
	sanguis::aura_type_vector const &,
	sanguis::buff_type_vector const &,
	sanguis::client::health_pair
);

}
}
}
}

#endif
