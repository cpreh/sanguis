#ifndef SANGUIS_CLIENT_PERK_TREE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_FWD_HPP_INCLUDED

#include <sanguis/client/perk/optional_info_fwd.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef
fcppt::container::tree::object<
	sanguis::client::perk::optional_info
>
tree;

}
}
}

#endif
