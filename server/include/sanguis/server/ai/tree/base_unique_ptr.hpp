#ifndef SANGUIS_SERVER_AI_TREE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/ai/tree/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::ai::tree
{

using
base_unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::ai::tree::base
>;

}

#endif
