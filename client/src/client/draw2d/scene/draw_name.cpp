#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sanguis/client/draw2d/scene/draw_name.hpp>
#include <sanguis/client/draw2d/scene/shown_name.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>


void
sanguis::client::draw2d::scene::draw_name(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::renderer::context::ffp &_render_context,
	sanguis::client::draw2d::scene::shown_name const &_name
)
{
	// TODO: Improve sge::font to make this easier
	sge::font::draw::static_text text(
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			_name.name().get()
		),
		sge::font::text_parameters(
			sge::font::align_h::left()
		),
		sge::font::vector(
			fcppt::cast::float_to_int<
				sge::font::unit
			>(
				_name.center().get().x()
			),
			fcppt::cast::float_to_int<
				sge::font::unit
			>(
				_name.center().get().y()
				-
				_name.radius().get()
			)
			-
			_font.metrics().height().get()
		),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
	);

	text.pos(
		text.pos()
		-
		text.rect().size()
		/
		fcppt::literal<
			sge::font::unit
		>(
			2
		)
	);

	text.draw_advanced(
		_render_context,
		sge::font::draw::set_matrices(
			false
		),
		sge::font::draw::set_states(
			false
		)
	);
}
