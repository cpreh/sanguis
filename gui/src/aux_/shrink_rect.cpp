#include <sanguis/gui/aux_/shrink_rect.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/math/box/shrink.hpp>


sge::rucksack::rect const
sanguis::gui::aux_::shrink_rect(
	sge::rucksack::rect const _rect,
	sge::rucksack::scalar const _scalar
)
{
	return
		fcppt::math::box::shrink(
			_rect,
			sge::rucksack::vector(
				_scalar,
				_scalar
			)
		);
}
