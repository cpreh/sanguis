#ifndef SANGUIS_SERVER_BUFFS_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_LIST_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

typedef boost::intrusive::list<
	sanguis::server::buffs::buff,
	boost::intrusive::constant_time_size<
		false
	>
> list;

}
}
}

#endif
