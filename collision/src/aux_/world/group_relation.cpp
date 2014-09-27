#include <sanguis/collision/aux_/world/group_pair.hpp>
#include <sanguis/collision/aux_/world/group_pair_static.hpp>
#include <sanguis/collision/aux_/world/group_pair_vector.hpp>
#include <sanguis/collision/aux_/world/group_relation.hpp>
#include <sanguis/collision/aux_/world/group_relation_static.hpp>
#include <sanguis/collision/world/group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

struct transform
{
	typedef
	sanguis::collision::aux_::world::group_pair_vector
	result_type;

	template<
		sanguis::collision::world::group Group1,
		sanguis::collision::world::group Group2
	>
	sanguis::collision::aux_::world::group_pair_vector
	operator()(
		sanguis::collision::aux_::world::group_pair_vector _state,
		sanguis::collision::aux_::world::group_pair_static<
			Group1,
			Group2
		>
	) const
	{
		_state.push_back(
			sanguis::collision::aux_::world::group_pair(
				Group1,
				Group2
			)
		);

		return
			_state;
	}
};

sanguis::collision::aux_::world::group_pair_vector const init{
	boost::fusion::fold(
		sanguis::collision::aux_::world::group_relation_static(),
		sanguis::collision::aux_::world::group_pair_vector(),
		transform()
	)
};

}

sanguis::collision::aux_::world::group_pair_vector const &
sanguis::collision::aux_::world::group_relation()
{
	return
		init;
}
