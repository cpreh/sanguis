#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_REF_HPP_INCLUDED

#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

using
with_ai_ref
=
fcppt::reference<
	sanguis::server::entities::with_ai
>;

}
}
}

#endif
