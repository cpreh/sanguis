#ifndef SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/perks/perk_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::perks
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::perks::perk
>;

}

#endif
