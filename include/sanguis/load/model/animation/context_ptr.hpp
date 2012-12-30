#ifndef SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_CONTEXT_PTR_HPP_INCLUDED

#include <sanguis/load/model/animation/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{
namespace animation
{

typedef std::unique_ptr<
	animation::context
> context_ptr;

}
}
}
}

#endif
