#ifndef SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_SET_HPP_INCLUDED

#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::ai
{

using
entity_set
=
std::unordered_set<
	sanguis::server::entities::with_body_ref
>;

}

#endif
