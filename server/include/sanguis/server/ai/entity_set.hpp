#ifndef SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED

#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/reference_wrapper_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

typedef
std::unordered_set<
	sanguis::server::entities::with_body_ref
>
entity_set;

}
}
}

#endif
