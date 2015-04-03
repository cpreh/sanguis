#include <sanguis/gui/impl/renderer/scoped.hpp>
#include <sanguis/gui/renderer/base_unique_ptr.hpp>
#include <sanguis/gui/renderer/create_scoped.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::gui::renderer::base_unique_ptr
sanguis::gui::renderer::create_scoped(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::gui::impl::renderer::scoped
		>(
			_renderer,
			_context
		);
}
