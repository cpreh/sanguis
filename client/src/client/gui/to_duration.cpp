#include <sanguis/duration.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sge/gui/duration.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sge::gui::duration
sanguis::client::gui::to_duration(
	sanguis::duration const &_duration
)
{
	return
		std::chrono::duration_cast<
			sge::gui::duration
		>(
			_duration
		);
}
