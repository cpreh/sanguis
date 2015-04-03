#include <sanguis/gui/gravity.hpp>
#include <sanguis/gui/impl/gravity_east.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sanguis::gui::impl::gravity_east(
	sanguis::gui::gravity const _gravity
)
{
	switch(
		_gravity
	)
	{
		case sanguis::gui::gravity::north_west:
		case sanguis::gui::gravity::south_west:
			return
				false;
		case sanguis::gui::gravity::south_east:
		case sanguis::gui::gravity::north_east:
			return
				true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
