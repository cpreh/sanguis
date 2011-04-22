#ifndef SANGUIS_CLIENT_PERK_FIND_INFO_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_FIND_INFO_HPP_INCLUDED

#include "tree.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace client
{
namespace perk
{

perk::tree const &
find_info(
	sanguis::perk_type::type,
	perk::tree const &
);

}
}
}

#endif
