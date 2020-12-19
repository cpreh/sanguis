#ifndef SANGUIS_SERVER_WEAPONS_LOG_CREF_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_LOG_CREF_HPP_INCLUDED

#include <sanguis/server/weapons/log_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

using
log_cref
=
fcppt::reference<
	sanguis::server::weapons::log const
>;

}
}
}

#endif
