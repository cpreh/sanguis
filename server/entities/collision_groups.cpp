#include "collision_groups.hpp"

sanguis::server::collision::group_vector const
sanguis::server::entities::collision_groups(
	entity_type::type const type_,
	team::type const team_
)
{
	collision::group_vector ret;

	switch(team_)
	{
	case team::players:
		ret.push_back(
			collision::group::player
		);
		break;
	case team::monsters:
		ret.push_back(
			collision::group::enemy
		);
		break;
	}

	return ret;
}
