#ifndef SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/collision/solidity.hpp>
#include <sanguis/server/entities/body_parameters_fwd.hpp>
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
		sanguis::server::collision::solidity const &
	);

	sge::projectile::shape::shared_base_ptr const
	shape() const;

	sanguis::server::collision::solidity const &
	solidity() const;
private:
	sge::projectile::shape::shared_base_ptr const shape_;

	sanguis::server::collision::solidity const solidity_;
};

}
}
}

#endif
