#ifndef SANGUIS_SERVER_BUFFS_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_MAP_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/buffs/buff_fwd.hpp>
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
	sanguis::entity_id,
	sanguis::server::buffs::buff
> map;

}
}
}

#endif
