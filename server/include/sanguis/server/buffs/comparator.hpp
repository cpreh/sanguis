#ifndef SANGUIS_SERVER_BUFFS_COMPARATOR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_COMPARATOR_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>


namespace sanguis::server::buffs
{

struct comparator
{
	bool
	operator()(
		sanguis::server::buffs::unique_ptr const &,
		sanguis::server::buffs::unique_ptr const &
	) const;

	bool
	operator()(
		sanguis::server::buffs::unique_ptr const &,
		sanguis::server::buffs::buff const &
	) const;

	bool
	operator()(
		sanguis::server::buffs::buff const &,
		sanguis::server::buffs::unique_ptr const &
	) const;

	using
	is_transparent
	=
	void;
};

}

#endif
