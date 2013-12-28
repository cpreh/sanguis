#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/draw2d/scene/hud.hpp>
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
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/time/output_tm.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::hud::hud(
	sge::font::object &_font_object,
	sge::renderer::device::ffp &_renderer,
	std::tm const &_time
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
	time_(
		_time
	),
	frames_counter_(),
	primary_weapon_(),
	secondary_weapon_(),
	weapon_text_(),
	name_text_()
{
	this->make_weapon_text();
}

sanguis::client::draw2d::scene::hud::~hud()
{
}

void
sanguis::client::draw2d::scene::hud::experience(
	sanguis::client::exp const _experience
)
{
	experience_ = _experience;
}

void
sanguis::client::draw2d::scene::hud::level(
	sanguis::client::level const _level
)
{
	level_ = _level;
}

void
sanguis::client::draw2d::scene::hud::time(
	std::tm const &_time
)
{
	time_ = _time;
}

void
sanguis::client::draw2d::scene::hud::weapon_description(
	sanguis::weapon_description const &_description
)
{
	this->weapon_text(
		sanguis::weapon_type_to_is_primary(
			_description.weapon_type()
		)
	) =
		_description.text();

	this->make_weapon_text();
}

void
sanguis::client::draw2d::scene::hud::remove_weapon(
	sanguis::is_primary_weapon const _is_primary
)
{
	this->weapon_text(
		_is_primary
	).clear();

	this->make_weapon_text();
}

void
sanguis::client::draw2d::scene::hud::draw(
	sge::renderer::context::ffp &_render_context
)
{
	frames_counter_.update();

	fcppt::io::ostringstream time_stream;

	fcppt::time::output_tm(
		time_stream,
		time_
	);

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
			+
			FCPPT_TEXT("\ntime: ")
			+
			time_stream.str()
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

	sge::font::draw::simple(
		renderer_,
		_render_context,
		font_object_,
		weapon_text_,
		sge::font::text_parameters(
			sge::font::align_h::right(
				width
			)
		),
		sge::font::vector::null(),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
	);
}

void
sanguis::client::draw2d::scene::hud::show_name(
	sanguis::client::draw2d::entities::name const &_name
)
{
	name_text_ =
		sge::font::from_fcppt_string(
			_name.get()
		);
}

void
sanguis::client::draw2d::scene::hud::clear_name()
{
	name_text_.clear();
}

void
sanguis::client::draw2d::scene::hud::make_weapon_text()
{
	weapon_text_.clear();

	weapon_text_ +=
		SGE_FONT_LIT("primary:\n");

	this->append_weapon_text(
		primary_weapon_
	);

	weapon_text_ +=
		SGE_FONT_LIT("\nsecondary:\n");

	this->append_weapon_text(
		secondary_weapon_
	);
}

void
sanguis::client::draw2d::scene::hud::append_weapon_text(
	sanguis::string_vector const &_text
)
{
	for(
		auto const &line
		:
		_text
	)
		weapon_text_
			+=
			sge::font::from_fcppt_string(
				line
			)
			+
			SGE_FONT_LIT('\n');
}

sanguis::string_vector &
sanguis::client::draw2d::scene::hud::weapon_text(
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
