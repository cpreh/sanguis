#ifndef SANGUIS_SERVER_BUFFS_CREATE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_CREATE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/buffs/optional_unique_ptr.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

typedef
std::function<
	sanguis::server::buffs::optional_unique_ptr (
		sanguis::server::entities::base &
	)
>
create_callback;

}
}
}

#endif
