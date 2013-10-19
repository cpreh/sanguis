#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
std::unique_ptr<
	sanguis::client::draw2d::entities::buffs::base
>
unique_ptr;

}
}
}
}
}

#endif
