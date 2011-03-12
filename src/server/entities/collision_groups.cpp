#include "collision_groups.hpp"

sanguis::server::collision::group_vector const
sanguis::server::entities::collision_groups(
	entity_type::type const type_,
	team::type const team_
)
{
	collision::group_vector ret;

	switch(
		type_
	)
	{
	case entity_type::enemy:
		ret.push_back(
			collision::group::enemy
		);
		break;
	case entity_type::pickup:
		ret.push_back(
			collision::group::pickup
		);
		break;
	case entity_type::friend_:
	case entity_type::sentry:
	case entity_type::player:
		ret.push_back(
			collision::group::player
		);
		break;
	case entity_type::projectile:
		switch(
			team_
		)
		{
		case team::players:
			ret.push_back(
				collision::group::projectile_player
			);
			break;
		case team::monsters:
			ret.push_back(
				collision::group::projectile_enemy
			);
			break;
		case team::neutral:
			break;
		}
		break;
	case entity_type::spawn:
		break;
	}

	return ret;
}
