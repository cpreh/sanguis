#include "generate_batches.hpp"
#include "batch.hpp"
#include "batch_grid.hpp"
#include "batch_size.hpp"
//#include "../../../../load/resource/textures.hpp"
#include <sanguis/creator/generator/generate.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/size.hpp>
//#include <sanguis/creator/geometry/shape_container.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/round_div_int.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::scene::world::batch_grid_unique_ptr
sanguis::client::draw2d::scene::world::generate_batches(
	sanguis::creator::generator::top_parameters const &_parameters,
	load::resource::textures const &_textures
)
{
	sanguis::creator::generator::result const generated(
		sanguis::creator::generator::generate(
			_parameters
		)
	);

	world::batch_grid_unique_ptr ret(
		fcppt::make_unique_ptr<
			world::batch_grid
		>(
			fcppt::math::dim::structure_cast<
				world::batch_grid::dim
			>(
				fcppt::algorithm::array_map<
					sanguis::creator::generator::size
				>(
					generated.size(),
					std::tr1::bind(
						fcppt::math::round_div_int<
							sanguis::creator::generator::size::value_type
						>,
						std::tr1::placeholders::_1,
						world::batch_size
					)
				)
			)
		)
	);

	return
		move(
			ret
		);
}
