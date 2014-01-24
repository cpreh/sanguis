#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/draw2d/scene/hud/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sanguis::client::draw2d::scene::hud::object::object(
	sge::font::object &_font_object,
	sge::renderer::device::ffp &_renderer
)
:
	font_object_(
		_font_object
	),
	renderer_(
		_renderer
	),
	experience_(
		0u
	),
	level_(
		0u
	),
	frames_counter_(),
	primary_weapon_(),
	secondary_weapon_(),
	name_text_()
{
}

sanguis::client::draw2d::scene::hud::object::~object()
{
}

void
sanguis::client::draw2d::scene::hud::object::experience(
	sanguis::client::exp const _experience
)
{
	experience_ = _experience;
}

void
sanguis::client::draw2d::scene::hud::object::level(
	sanguis::client::level const _level
)
{
	level_ = _level;
}

void
sanguis::client::draw2d::scene::hud::object::add_weapon(
	sanguis::weapon_description const &_description
)
{
	this->weapon_description(
		sanguis::weapon_type_to_is_primary(
			_description.weapon_type()
		)
	) =
		sanguis::optional_weapon_description(
			_description
		);
}

void
sanguis::client::draw2d::scene::hud::object::remove_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	this->weapon_description(
		_is_primary
	) =
		sanguis::optional_weapon_description();
}

void
sanguis::client::draw2d::scene::hud::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	frames_counter_.update();

	sge::font::align_h::max_width const width(
		fcppt::cast::size<
			sge::font::unit
		>(
			fcppt::cast::to_signed(
				sge::renderer::target::viewport_size(
					_render_context.target()
				).w()
			)
		)
	);

	sge::font::draw::simple(
		renderer_,
		_render_context,
		font_object_,
		sge::font::from_fcppt_string(
			(
				fcppt::format(
					FCPPT_TEXT("exp: %1%, level: %2%, fps: %3%")
				)
				% experience_
				% level_
				% frames_counter_.frames_str()
			).str()
		)
		+
		SGE_FONT_LIT("\n\n")
		+
		name_text_,
		sge::font::text_parameters(
			sge::font::align_h::left(
				width
			)
		),
		sge::font::vector::null(),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
	);
}

void
sanguis::client::draw2d::scene::hud::object::show_name(
	sanguis::client::draw2d::entities::name const &_name
)
{
	name_text_ =
		sge::font::from_fcppt_string(
			_name.get()
		);
}

void
sanguis::client::draw2d::scene::hud::object::clear_name()
{
	name_text_.clear();
}

sanguis::optional_weapon_description &
sanguis::client::draw2d::scene::hud::object::weapon_description(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		_is_primary.get()
		?
			primary_weapon_
		:
			secondary_weapon_
		;
}
