#ifndef SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/perks/perk_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

typedef
fcppt::unique_ptr<
	sanguis::server::perks::perk
>
unique_ptr;

}
}
}

#endif
