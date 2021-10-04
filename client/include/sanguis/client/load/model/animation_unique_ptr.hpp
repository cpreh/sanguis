#ifndef SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_ANIMATION_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/animation_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::client::load::model
{

using
animation_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::load::model::animation
>;

}

#endif
