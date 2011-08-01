#ifndef SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED

#include "unique_ptr.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

unique_ptr
create(
	sanguis::diff_clock const &,
	perk_type::type
);

}
}
}

#endif
