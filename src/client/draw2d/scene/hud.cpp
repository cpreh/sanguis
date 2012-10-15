#include <sanguis/client/draw2d/scene/hud.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/time/output_tm.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

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
	frames_counter_()
{
}

void
sanguis::client::draw2d::scene::hud::experience(
	client::exp const _experience
)
{
	experience_ = _experience;
}

void
sanguis::client::draw2d::scene::hud::level(
	client::level const _level
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
			+ time_stream.str()
		),
		sge::font::text_parameters(
			sge::font::align_h::left
		)
		.max_width(
			300 // FIXME
		),
		sge::font::vector::null(),
		sge::image::colors::white()
	);
}
