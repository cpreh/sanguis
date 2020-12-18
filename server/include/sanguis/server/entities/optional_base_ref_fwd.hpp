#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_BASE_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

using
optional_base_ref
=
fcppt::optional::reference<
	sanguis::server::entities::base
>;

}
}
}

#endif
