#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/make_size.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/scale.hpp>
#include <sanguis/collision/unit.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::collision::dim2 const
sanguis::collision::make_size(
	sanguis::collision::radius const _radius
)
{
	return
		fcppt::math::dim::fill<
			sanguis::collision::dim2::dim_wrapper::value
		>(
			_radius.get()
			*
			static_cast<
				sanguis::collision::unit
			>(
				sanguis::collision::scale()
			)
		);
}
