#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/client/draw2d/scene/world/clamp_size.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::creator::pos
sanguis::client::draw2d::scene::world::clamp_size(
	sanguis::creator::pos const &_pos,
	sanguis::creator::size const &_size
)
{
	sanguis::creator::pos ret{
		fcppt::no_init()
	};

	for(
		sanguis::creator::pos::size_type index(
			0u
		);
		index < sanguis::creator::pos::dim_wrapper::value;
		++index
	)
		ret[
			index
		] =
			std::min(
				_pos[
					index
				],
				_size[
					index
				]
			);

	return
		ret;
}
