#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_FRIEND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_FRIEND_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../../../friend_type.hpp" 

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
friend_(
	entities::model::parameters const &,
	friend_type::type
);

}
}
}
}

#endif
