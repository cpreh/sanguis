#include <sanguis/client/draw2d/font_color_format.hpp>
#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sanguis/client/draw2d/scene/state/scoped_text.hpp>
#include <sanguis/client/draw2d/scene/state/text.hpp>
#include <sge/font/draw/create_ffp_sampler.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/map.hpp>


sanguis::client::draw2d::scene::state::text::text(
	sge::renderer::device::ffp_ref const _device
)
:
	sanguis::client::draw2d::scene::state::base(),
	sampler_(
		sge::font::draw::create_ffp_sampler(
			_device,
			sanguis::client::draw2d::font_color_format()
		)
	)
{
}

sanguis::client::draw2d::scene::state::text::~text()
= default;

sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
sanguis::client::draw2d::scene::state::text::create_scoped(
	sge::renderer::context::ffp_ref const _render_context
) const
{
	return
		fcppt::optional::map(
			sampler_,
			[
				&_render_context
			](
				sge::renderer::state::ffp::sampler::object_unique_ptr const &_sampler
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sanguis::client::draw2d::scene::state::scoped
					>(
						fcppt::make_unique_ptr<
							sanguis::client::draw2d::scene::state::scoped_text
						>(
							_render_context,
							fcppt::make_cref(
								*_sampler
							)
						)
					);
			}
		);
}
