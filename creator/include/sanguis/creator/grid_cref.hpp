#ifndef SANGUIS_CREATOR_GRID_CREF_HPP_INCLUDED
#define SANGUIS_CREATOR_GRID_CREF_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace creator
{

using
grid_cref
=
fcppt::reference<
	sanguis::creator::grid const
>;

}
}

#endif
