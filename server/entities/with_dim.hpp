#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "with_dim_fwd.hpp"
#include "base.hpp"
#include "../dim_type.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include <fcppt/math/dim/basic_decl.hpp>

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
public:
	pos_type const
	pos() const;
protected:
	explicit with_dim(
		dim_type const &
	);

	~with_dim();

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
