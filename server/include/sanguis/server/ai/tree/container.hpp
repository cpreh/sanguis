#ifndef SANGUIS_SERVER_AI_TREE_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_CONTAINER_HPP_INCLUDED

#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::ai::tree
{

using
container
=
std::vector<
	sanguis::server::ai::tree::base_unique_ptr
>;

}

#endif
