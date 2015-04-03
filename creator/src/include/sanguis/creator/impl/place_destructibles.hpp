#ifndef SANGUIS_CREATOR_IMPL_PLACE_DESTRUCTIBLES_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_DESTRUCTIBLES_HPP_INCLUDED

#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

sanguis::creator::destructible_container
place_destructibles(
	sanguis::creator::grid &,
	sanguis::creator::impl::random::generator &
);

}
}
}

#endif
