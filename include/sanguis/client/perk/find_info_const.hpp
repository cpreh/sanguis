#ifndef SANGUIS_CLIENT_PERK_FIND_INFO_CONST_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_FIND_INFO_CONST_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/client/perk/tree_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

sanguis::client::perk::tree const &
find_info_const(
	sanguis::perk_type,
	sanguis::client::perk::tree const &
);

}
}
}

#endif
