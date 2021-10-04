#ifndef SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::buffs
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::buffs::buff
>;

}

#endif
