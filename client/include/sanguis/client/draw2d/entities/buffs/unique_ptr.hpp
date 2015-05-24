#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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

typedef
fcppt::unique_ptr<
	sanguis::client::draw2d::entities::buffs::base
>
unique_ptr;

}
}
}
}
}

#endif
