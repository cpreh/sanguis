#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "base.hpp"
#include "../dim_type.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include <sge/math/dim/basic_decl.hpp>

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

	~with_dim();

	dim_type const &
	dim() const;

	pos_type const
	pos() const;
private:
	space_unit
	radius() const;

	dim_type const dim_;
};

}
}
}

#endif
