#include <sanguis/collision/aux/world/group_pair.hpp>
#include <sanguis/collision/aux/world/group_relation.hpp>
#include <sanguis/collision/aux/world/simple/groups_collide.hpp>
#include <sanguis/collision/world/group_field.hpp>


namespace
{

bool
test_pair(
	sanguis::collision::world::group_field const &_field1,
	sanguis::collision::world::group_field const &_field2,
	sanguis::collision::aux::world::group_pair const &_pair
)
{
	return
		(
			_field1
			&
			_pair.first
		)
		&&
		(
			_field2
			&
			_pair.second
		);
}

}

bool
sanguis::collision::aux::world::simple::groups_collide(
	sanguis::collision::world::group_field const &_field1,
	sanguis::collision::world::group_field const &_field2
)
{
	for(
		auto const pair
		:
		sanguis::collision::aux::world::group_relation()
	)
		if(
			test_pair(
				_field1,
				_field2,
				pair
			)
			||
			test_pair(
				_field2,
				_field1,
				pair
			)
		)
			return true;

	return false;
}
