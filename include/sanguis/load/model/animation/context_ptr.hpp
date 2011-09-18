#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED

#include <sanguis/load/model/animation/context_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{
namespace animation
{

typedef fcppt::unique_ptr<
	animation::context
> context_ptr;

}
}
}
}

#endif
