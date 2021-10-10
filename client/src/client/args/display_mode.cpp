#include <sanguis/client/args/display_mode.hpp>
#include <sanguis/client/args/resolution.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <fcppt/optional/map.hpp>

sge::renderer::display_mode::optional_object
sanguis::client::args::display_mode(sanguis::client::args::result const &_result)
{
  return fcppt::optional::map(
      sanguis::client::args::resolution(_result),
      [](sge::renderer::screen_size const &_size)
      {
        return sge::renderer::display_mode::object{
            sge::renderer::display_mode::pixel_size{_size},
            sge::renderer::display_mode::optional_dimensions(),
            sge::renderer::display_mode::optional_refresh_rate()};
      });
}
