#ifndef SANGUIS_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/load/model/animation_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef
std::unique_ptr<
	sanguis::load::model::animation
>
animation_unique_ptr;

}
}
}

#endif
