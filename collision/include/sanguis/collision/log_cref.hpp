#ifndef SANGUIS_COLLISION_LOG_CREF_HPP_INCLUDED
#define SANGUIS_COLLISION_LOG_CREF_HPP_INCLUDED

#include <sanguis/collision/log_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::collision
{

using
log_cref
=
fcppt::reference<
	sanguis::collision::log const
>;

}

#endif
