#ifndef SANGUIS_CLIENT_PERK_OPTIONAL_INFO_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_OPTIONAL_INFO_FWD_HPP_INCLUDED

#include <sanguis/client/perk/info_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef
fcppt::optional<
	sanguis::client::perk::info
> optional_info;

}
}
}

#endif