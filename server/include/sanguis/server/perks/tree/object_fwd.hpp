#ifndef SANGUIS_SERVER_PERKS_TREE_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/server/perks/tree/status_fwd.hpp>
#include <fcppt/container/tree/object_fwd.hpp>

namespace sanguis::server::perks::tree
{

using object = fcppt::container::tree::object<sanguis::server::perks::tree::status>;

}

#endif
