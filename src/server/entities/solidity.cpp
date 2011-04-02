#include "solidity.hpp"
#include "../collision/solidity.hpp"
#include "../../exception.hpp"
#include <sge/projectile/body/mass.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <fcppt/text.hpp>

sanguis::server::collision::solidity const
sanguis::server::entities::solidity(
	sanguis::entity_type::type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::entity_type::enemy:
	case sanguis::entity_type::friend_:
	case sanguis::entity_type::player:
	case sanguis::entity_type::sentry:
		return
			collision::solidity(
				sge::projectile::body::solidity::solid(
					sge::projectile::body::mass(
						1
					)
				)
			);
	case sanguis::entity_type::pickup:
	case sanguis::entity_type::projectile:
	case sanguis::entity_type::spawn:
		return
			collision::solidity(
				sge::projectile::body::solidity::nonsolid()
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid entity_type in entities::solidity!")
	);
}
