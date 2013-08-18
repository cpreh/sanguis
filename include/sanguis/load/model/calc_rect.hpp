#ifndef SANGUIS_LOAD_MODEL_CALC_RECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CALC_RECT_HPP_INCLUDED

#include <sanguis/load/model/cell_size_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/size_type.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sge::renderer::lock_rect const
calc_rect(
	sge::renderer::lock_rect const &,
	sanguis::load::model::cell_size,
	sge::renderer::size_type index
);

}
}
}

#endif
