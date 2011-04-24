#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_ENEMY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_ENEMY_HPP_INCLUDED

#include "../entities/unique_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../../../enemy_type.hpp" 

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::unique_ptr
enemy(
	entities::model::parameters const &,
	enemy_type::type
);

}
}
}
}

#endif
