#ifndef SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TREE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/perk/tree_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef std::unique_ptr<
	sanguis::client::perk::tree
> tree_unique_ptr;

}
}
}

#endif
