#include <sanguis/random_generator.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/insert_with_id_pair.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>
#include <sanguis/server/world/place_multiple.hpp>
#include <sanguis/server/world/place_with_id_callback.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/distribution/transform/strong_typedef.hpp>


sanguis::server::world::insert_with_id_pair_container
sanguis::server::world::place_multiple(
	sanguis::random_generator &_random_generator,
	sanguis::server::world::place_with_id_callback const &_place,
	sanguis::creator::pos const _pos,
	sanguis::server::radius const _radius
)
{
	sanguis::server::center const center(
		sanguis::server::world::grid_pos_to_center(
			_pos
		)
	);

	typedef
	fcppt::random::distribution::parameters::uniform_real<
		sanguis::server::space_unit
	>
	uniform_space_unit;

	typedef
	fcppt::random::distribution::parameters::uniform_real<
		sanguis::server::angle
	>
	uniform_angle;

	sanguis::server::space_unit const tile_size_half(
		fcppt::cast::int_to_float<
			sanguis::server::space_unit
		>(
			sanguis::creator::tile_size::value
			/
			2
		)
	);

	sanguis::server::space_unit const space(
		tile_size_half
		-
		_radius.get()
	);

	if(
		space <= 0.f
	)
		return
			sanguis::server::world::insert_with_id_pair_container();

	auto random_coordinate(
		fcppt::random::make_variate(
			_random_generator,
			fcppt::random::distribution::make_basic(
				uniform_space_unit(
					uniform_space_unit::min(
						-space
					),
					uniform_space_unit::sup(
						+space
					)
				)
			)
		)
	);

	auto random_angle(
		fcppt::random::make_variate(
			_random_generator,
			fcppt::random::distribution::make_basic(
				uniform_angle(
					uniform_angle::min(
						sanguis::server::angle(
							0.f
						)
					),
					uniform_angle::sup(
						sanguis::server::angle(
							fcppt::math::twopi<
								sanguis::server::space_unit
							>()
						)
					)
				)
			)
		)
	);

	sanguis::server::space_unit const num_fits(
		tile_size_half
		/
		_radius.get()
	);

	return
		fcppt::algorithm::map<
			sanguis::server::world::insert_with_id_pair_container
		>(
			fcppt::make_int_range_count(
				fcppt::cast::to_unsigned(
					fcppt::cast::float_to_int<
						int
					>(
						num_fits
						*
						num_fits
					)
				)
			),
			[
				center,
				&random_coordinate,
				&random_angle,
				&_place
			](
				unsigned
			)
			{
				return
					sanguis::server::world::insert_with_id_pair(
						_place(),
						sanguis::server::entities::insert_parameters(
							sanguis::server::center(
								sanguis::server::vector(
									random_coordinate(),
									random_coordinate()
								)
							)
							+
							center,
							random_angle()
						)
					);
			}
		);
}
