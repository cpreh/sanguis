#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_CREATE_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace buffs
{

sanguis::client::draw2d::entities::buffs::unique_ptr
create(
	sanguis::buff_type
);

}
}
}
}
}

#endif
