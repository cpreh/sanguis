#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
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
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::client::draw2d::scene::hover::name::name(
	sanguis::client::draw2d::scene::hover::parameters const &_parameters,
	sanguis::client::draw2d::entities::hover::name const &_name
)
:
	text_(
		_parameters.renderer(),
		_parameters.font(),
		sge::font::from_fcppt_string(
			_name.get()
		),
		sge::font::text_parameters(
			sge::font::align_h::left()
		),
		sge::font::vector(
			_parameters.center().get().x(),
			_parameters.center().get().y()
			-
			_parameters.radius().get()
			-
			_parameters.font().metrics().height().get()
		),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
	)
{
	// TODO: Improve sge::font to make this easier
	text_.pos(
		text_.pos()
		-
		text_.rect().size()
		/
		fcppt::literal<
			sge::font::unit
		>(
			2
		)
	);
}

sanguis::client::draw2d::scene::hover::name::name(
	name &&
) = default;

sanguis::client::draw2d::scene::hover::name &
sanguis::client::draw2d::scene::hover::name::operator=(
	name &&
) = default;

sanguis::client::draw2d::scene::hover::name::~name()
{
}

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
