#ifndef SANGUIS_SERVER_PERKS_TREE_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/server/perks/tree/optional_status_fwd.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

typedef fcppt::container::tree::object<
	sanguis::server::perks::tree::optional_status
> object;

}
}
}
}

#endif
