#ifndef SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/perks/perk_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

typedef fcppt::unique_ptr<
	perk
> unique_ptr;

}
}
}

#endif
