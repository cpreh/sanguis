#include <sanguis/gui/needed_width.hpp>
#include <sanguis/gui/needed_width_from_strings.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/left.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::gui::needed_width const
sanguis::gui::needed_width_from_strings(
	sge::font::object &_font,
	sanguis::gui::string_container const &_strings
)
{
	return
		fcppt::algorithm::fold(
			_strings,
			sanguis::gui::needed_width(
				0
			),
			[
				&_font
			](
				sge::font::string const &_text,
				sanguis::gui::needed_width const _prev_width
			)
			{
				return
					sanguis::gui::needed_width(
						std::max(
							_prev_width.get(),
							_font.create_text(
								_text,
								sge::font::text_parameters(
									sge::font::align_h::left()
								).flags(
									sge::font::flags_field{
										sge::font::flags::no_multi_line
									}
								)
							)->logical_size().w()
						)
					);
			}
		);
}
