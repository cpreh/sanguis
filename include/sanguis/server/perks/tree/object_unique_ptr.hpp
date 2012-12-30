#ifndef SANGUIS_SERVER_PERKS_TREE_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/perks/tree/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

typedef std::unique_ptr<
	sanguis::server::perks::tree::object
> object_unique_ptr;

}
}
}
}

#endif
