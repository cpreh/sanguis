#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_CREATE_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>


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
	sanguis::diff_clock const &,
	sanguis::client::draw2d::sprite::normal::system &,
	sanguis::client::load::model::collection const &,
	sanguis::client::draw2d::entities::model::object const &,
	sanguis::buff_type
);

}
}
}
}
}

#endif
