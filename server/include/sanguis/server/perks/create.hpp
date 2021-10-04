#ifndef SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>


namespace sanguis::server::perks
{

sanguis::server::perks::unique_ptr
create(
	sanguis::diff_clock_cref,
	sanguis::random_generator_ref,
	sanguis::perk_type
);

}

#endif
