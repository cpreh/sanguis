#include <sanguis/client/args/optional_resolution.hpp>
#include <sanguis/client/args/resolution.hpp>
#include <sanguis/client/args/result.hpp>
#include <sanguis/client/args/labels/display_height.hpp>
#include <sanguis/client/args/labels/display_width.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/record/get.hpp>


sanguis::client::args::optional_resolution
sanguis::client::args::resolution(
	sanguis::client::args::result const &_result
)
{
	return
		fcppt::optional::apply(
			[](
				sge::renderer::screen_unit const _width,
				sge::renderer::screen_unit const _height
			)
			{
				return
					sge::renderer::screen_size{
						_width,
						_height
					};
			},
			fcppt::record::get<
				sanguis::client::args::labels::display_width
			>(
				_result
			),
			fcppt::record::get<
				sanguis::client::args::labels::display_height
			>(
				_result
			)
		);
}
