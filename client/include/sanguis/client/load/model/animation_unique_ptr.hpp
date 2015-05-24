#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/animation_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

typedef
fcppt::unique_ptr<
	sanguis::client::load::model::animation
>
animation_unique_ptr;

}
}
}
}

#endif
