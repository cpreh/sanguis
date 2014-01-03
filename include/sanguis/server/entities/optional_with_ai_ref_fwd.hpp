#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_AI_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_AI_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional<
	sanguis::server::entities::with_ai &
>
optional_with_ai_ref;

}
}
}

#endif
