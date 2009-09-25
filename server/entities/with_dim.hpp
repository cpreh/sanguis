#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "base.hpp"
#include "../dim_type.hpp"
#include "../space_unit.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class with_dim
:
	public virtual base
{
protected:
	explicit with_dim(
		dim_type const &
	);

	dim_type const &
	dim() const;
private:
	space_unit
	radius() const;

	dim_type const dim_;
};

}
}
}

#endif
