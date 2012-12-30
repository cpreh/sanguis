#include <sanguis/entity_type.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/collision_groups.hpp>


sanguis::server::collision::group_vector const
sanguis::server::entities::collision_groups(
	sanguis::entity_type const _type,
	sanguis::server::team const _team
)
{
	sanguis::server::collision::group_vector ret;

	switch(
		_type
	)
	{
	case sanguis::entity_type::enemy:
		ret.push_back(
			sanguis::server::collision::group::enemy
		);
		break;
	case sanguis::entity_type::pickup:
		ret.push_back(
			sanguis::server::collision::group::pickup
		);
		break;
	case sanguis::entity_type::friend_:
	case sanguis::entity_type::sentry:
	case sanguis::entity_type::player:
		ret.push_back(
			sanguis::server::collision::group::player
		);
		break;
	case sanguis::entity_type::projectile:
		switch(
			_team
		)
		{
		case sanguis::server::team::players:
			ret.push_back(
				sanguis::server::collision::group::projectile_player
			);
			break;
		case sanguis::server::team::monsters:
			ret.push_back(
				sanguis::server::collision::group::projectile_enemy
			);
			break;
		case sanguis::server::team::neutral:
			break;
		}
		break;
	case sanguis::entity_type::spawn:
		break;
	}

	return ret;
}
