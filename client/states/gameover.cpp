#include "gameover.hpp"
#include "menu.hpp"
#include "args/gameover.hpp"
#include "../../resolution_type.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../cursor/object.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/image2d/loader.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::gui::dim const
dialog_size(
	sanguis::resolution_type const &resolution_
)
{
	float const
		scale_x = 0.5f,
		scale_y = 0.8f;
	
	return
		sge::gui::dim(
			static_cast<sge::gui::unit>(
				static_cast<float>(
					resolution_.w()
				)
				* scale_x
			),
			static_cast<sge::gui::unit>(
				static_cast<float>(
					resolution_.h()
				)
				* scale_y
			)
		);
}

sge::gui::point const
dialog_pos(
	sanguis::resolution_type const &resolution_
)
{
	return 
		fcppt::math::dim::structure_cast<sge::gui::point>(
			resolution_
		) /
		static_cast<sge::gui::unit>(2)-
		fcppt::math::dim::structure_cast<sge::gui::point>(
			dialog_size(
				resolution_
			)
		) /
		static_cast<sge::gui::unit>(2);
}
}

sanguis::client::states::gameover::gameover(
	my_context _ctx,
	args::gameover const &_args
)
:
	my_base(
		_ctx
	),
	manager_(
		context<machine>().renderer(),
		context<machine>().keyboard(),
		context<machine>().mouse(),
		sge::gui::skins::ptr(
			fcppt::make_unique_ptr<
				sge::gui::skins::standard
			>(
				context<machine>().font_metrics()
			)
		),
		context<machine>().cursor()
	),
	background_(
		manager_,
		sge::gui::widgets::parameters()
			.pos(
				dialog_pos(
					context<machine>().renderer()->screen_size()
				)
			)
			.size(
				dialog_size(
					context<machine>().renderer()->screen_size()
				)
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	dead_label_(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)),
		SGE_FONT_TEXT_LIT("You are dead.")
	),
	score_(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			)
			.layout(
				fcppt::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	names_head_(
		score_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)
			),
		SGE_FONT_TEXT_LIT("Name(s):")
	),
	score_head_(
		score_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,0)
			),
		SGE_FONT_TEXT_LIT("Score:")
	),
	names_text_(
		score_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			),
		sge::font::text::from_fcppt_string(
			fcppt::algorithm::join_strings(
				_args.names(),
				FCPPT_TEXT(", ")
			)
		)
	),
	score_text_(
		score_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,1)
			),
		fcppt::lexical_cast<
			sge::font::text::string
		>(
			_args.score()
		)
	),
	buttons_return_(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,2)
			),
		SGE_FONT_TEXT_LIT("Main menu")
	),
	return_connection_(
		buttons_return_.register_clicked(
			std::tr1::bind(
				&gameover::return_clicked,
				this
			)
		)
	)
{
	context<machine>().cursor()->visible(true);
}

boost::statechart::result
sanguis::client::states::gameover::react(
	events::tick const &
)
{
	manager_.update();

	manager_.draw();

	return discard_event();
}

boost::statechart::result
sanguis::client::states::gameover::react(
	events::menu const &
)
{
	return transit<menu>();
}

boost::statechart::result
sanguis::client::states::gameover::react(
	events::message const &_message
)
{
	return
		handle_default_msg(
			*_message.value()
		);
}

boost::statechart::result
sanguis::client::states::gameover::handle_default_msg(
	messages::base const &
)
{
	return discard_event();
}

void
sanguis::client::states::gameover::return_clicked()
{
	post_event(
		events::menu()
	);
}
