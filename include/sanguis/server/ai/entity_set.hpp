#ifndef SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED

#include <sanguis/server/entities/with_health_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

// TODO: Use optionals here!
typedef
std::unordered_set<
	sanguis::server::entities::with_health *
>
entity_set;

}
}
}

#endif
