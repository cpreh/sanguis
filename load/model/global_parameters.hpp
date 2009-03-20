#ifndef SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include "optional_delay.hpp"
#include <sge/renderer/dim_type.hpp>
#include <sge/math/dim/basic_impl.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

struct global_parameters {
	global_parameters(
		sge::renderer::dim_type const &cell_size,
		optional_delay const &);
	
	sge::renderer::dim_type const &
	cell_size() const;

	optional_delay const &
	delay() const;
private:
	sge::renderer::dim_type const cell_size_;
	optional_delay const delay_;
};

}
}
}

#endif
