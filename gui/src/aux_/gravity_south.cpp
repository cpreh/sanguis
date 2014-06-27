#include <sanguis/gui/gravity.hpp>
#include <sanguis/gui/aux_/gravity_south.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sanguis::gui::aux_::gravity_south(
	sanguis::gui::gravity const _gravity
)
{
	switch(
		_gravity
	)
	{
		case sanguis::gui::gravity::north_east:
		case sanguis::gui::gravity::north_west:
			return
				false;
		case sanguis::gui::gravity::south_east:
		case sanguis::gui::gravity::south_west:
			return
				true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
