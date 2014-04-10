#ifndef SANGUIS_SERVER_PERKS_TREE_OPTIONAL_STATUS_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OPTIONAL_STATUS_FWD_HPP_INCLUDED

#include <sanguis/server/perks/tree/status_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

typedef fcppt::optional<
	sanguis::server::perks::tree::status
> optional_status;

}
}
}
}

#endif
