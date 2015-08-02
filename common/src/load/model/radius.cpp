#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/load/model/radius.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::collision::radius const
sanguis::load::model::radius(
	sanguis::model::cell_size const _cell_size
)
{
	auto const quad_half(
		[](
			sanguis::model::cell_size_unit const _val
		)
		->
		sanguis::collision::unit
		{
			return
				fcppt::cast::int_to_float<
					sanguis::collision::unit
				>(
					_val
					*
					_val
				)
				/
				fcppt::literal<
					sanguis::collision::unit
				>(
					4
				);
		}
	);

	return
		sanguis::collision::radius(
			std::sqrt(
				quad_half(
					_cell_size.get().w()
				)
				+
				quad_half(
					_cell_size.get().h()
				)
			)
			*
			fcppt::literal<
				sanguis::collision::unit
			>(
				0.4f
			)
			*
			boost::units::si::meter
		);
}
