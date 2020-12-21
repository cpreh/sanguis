#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::client::draw2d::scene::hover::name::name(
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::radius const _radius,
	sanguis::client::draw2d::entities::hover::name const &_name
)
:
	text_(
		_renderer,
		_font,
		sge::font::from_fcppt_string(
			_name.text()
		),
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::left()
			)
		),
		sge::font::vector(
			_center.get().x(),
			_center.get().y()
			-
			_radius.get()
			-
			_font->metrics().height().get()
		),
		_name.color(),
		sge::renderer::texture::emulate_srgb::no
	)
{
	// TODO(philipp): Improve sge::font to make this easier
	text_.pos(
		text_.pos()
		-
		(
			text_.rect().size()
			/
			fcppt::literal<
				sge::font::unit
			>(
				2
			)
		).get_unsafe()
	);
}

sanguis::client::draw2d::scene::hover::name::name(
	name &&
)
noexcept
= default;

sanguis::client::draw2d::scene::hover::name &
sanguis::client::draw2d::scene::hover::name::operator=(
	name &&
)
noexcept
= default;

sanguis::client::draw2d::scene::hover::name::~name()
= default;

void
sanguis::client::draw2d::scene::hover::name::draw(
	sge::renderer::context::ffp &_render_context
)
{
	text_.draw_advanced(
		_render_context,
		sge::font::draw::set_matrices(
			false
		),
		sge::font::draw::set_states(
			false
		)
	);
}
