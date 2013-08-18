#ifndef SANGUIS_LOAD_MODEL_CELL_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CELL_SIZE_FWD_HPP_INCLUDED

#include <sge/renderer/dim2_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::dim2,
	cell_size
);

}
}
}

#endif
