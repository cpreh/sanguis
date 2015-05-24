#include <sanguis/gui/impl/renderer/stateless.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/renderer/base_unique_ptr.hpp>
#include <sanguis/gui/renderer/create_stateless.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::gui::renderer::base_unique_ptr
sanguis::gui::renderer::create_stateless(
	sge::renderer::device::ffp &_renderer
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::gui::renderer::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::gui::impl::renderer::stateless
			>(
				_renderer
			)
		);
}
