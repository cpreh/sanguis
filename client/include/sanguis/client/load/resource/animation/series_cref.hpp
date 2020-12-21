#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_CREF_HPP_INCLUDED

#include <sanguis/client/load/resource/animation/series_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{
namespace animation
{

using
series_cref
=
fcppt::reference<
	sanguis::client::load::resource::animation::series const
>;

}
}
}
}
}

#endif
