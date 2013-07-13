#ifndef SANGUIS_SERVER_BUFFS_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_MAP_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

typedef boost::ptr_map<
	sanguis::server::entities::with_buffs *,
	sanguis::server::buffs::buff
> map;

}
}
}

#endif
