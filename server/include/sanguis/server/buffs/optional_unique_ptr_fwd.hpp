#ifndef SANGUIS_SERVER_BUFFS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_OPTIONAL_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

typedef
fcppt::optional<
	sanguis::server::buffs::unique_ptr
>
optional_unique_ptr;

}
}
}

#endif
