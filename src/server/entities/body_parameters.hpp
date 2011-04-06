#ifndef SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED

#include "body_parameters_fwd.hpp"
#include "../collision/solidity.hpp"
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class body_parameters
{
	FCPPT_NONASSIGNABLE(
		body_parameters
	);
public:
	body_parameters(
		sge::projectile::shape::shared_base_ptr,
		collision::solidity const &
	);
	
	sge::projectile::shape::shared_base_ptr const
	shape() const;

	collision::solidity const &
	solidity() const;
private:
	sge::projectile::shape::shared_base_ptr const shape_;

	collision::solidity const solidity_;
};

}
}
}

#endif
