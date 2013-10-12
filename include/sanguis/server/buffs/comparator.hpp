#ifndef SANGUIS_SERVER_BUFFS_COMPARATOR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_COMPARATOR_HPP_INCLUDED

#include <sanguis/server/buffs/unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

struct comparator
{
	bool
	operator()(
		sanguis::server::buffs::unique_ptr const &,
		sanguis::server::buffs::unique_ptr const &
	) const;
};

}
}
}

#endif
