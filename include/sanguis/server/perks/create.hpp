#ifndef SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

sanguis::server::perks::unique_ptr
create(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::perk_type
);

}
}
}

#endif
