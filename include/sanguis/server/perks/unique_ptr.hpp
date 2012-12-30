#ifndef SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/perks/perk_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

typedef std::unique_ptr<
	sanguis::server::perks::perk
> unique_ptr;

}
}
}

#endif
