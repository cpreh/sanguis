#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED

#include "animation_context_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef fcppt::unique_ptr<
	animation_context
> animation_context_ptr;

}
}
}

#endif
