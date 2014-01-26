#include <sanguis/duration.hpp>
#include <sanguis/client/to_gui_duration.hpp>
#include <sanguis/gui/duration.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::gui::duration
sanguis::client::to_gui_duration(
	sanguis::duration const &_duration
)
{
	return
		std::chrono::duration_cast<
			sanguis::gui::duration
		>(
			_duration
		);
}
