#ifndef SANGUIS_SERVER_AI_TREE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/tree/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

typedef
std::unique_ptr<
	sanguis::server::ai::tree::base
>
base_unique_ptr;

}
}
}
}

#endif
