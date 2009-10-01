#include "gameover.hpp"
#include "menu.hpp"
#include "../perk_cast.hpp"
#include "../../media_path.hpp"
#include "../../resolution.hpp"
#include "../../messages/create.hpp"
#include "../../messages/unwrap.hpp"
#include "../../tick_event.hpp"
#include "../menu_event.hpp"
#include "../message_event.hpp"
#include "../cursor/object.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/grid.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/math/dim/dim.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/image/loader.hpp>
#include <sge/systems/instance.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/algorithm/join_strings.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <tr1/functional>

namespace
{
sge::gui::dim const dialog_size()
{
	float const scale_x = 0.5f,
	            scale_y = 0.8f;
	
	return sge::gui::dim(
		static_cast<sge::gui::unit>(
			static_cast<float>(
				sanguis::resolution().w())*scale_x),
		static_cast<sge::gui::unit>(
			static_cast<float>(
				sanguis::resolution().h())*scale_y));
}

sge::gui::point const dialog_pos()
{
	return 
		sge::math::dim::structure_cast<sge::gui::point>(
			sanguis::resolution())/
		static_cast<sge::gui::unit>(2)-
		sge::math::dim::structure_cast<sge::gui::point>(
			dialog_size())/
		static_cast<sge::gui::unit>(2);
}
}

sanguis::client::states::gameover::gameover(
	my_context ctx
)
:
	my_base(ctx),
	m_(
		context<machine>().sys().renderer(),
		context<machine>().sys().input_system(),
		sge::gui::skins::ptr(
			new sge::gui::skins::standard(
				context<machine>().sys().font_system()
			)
		),
		context<machine>().cursor()
	),
	background_(
		m_,
		sge::gui::widgets::parameters()
			.pos(dialog_pos())
			.size(dialog_size())
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	dead_label(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)),
		SGE_TEXT("You are dead.")
	),
	score(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			)
			.layout(
				sge::make_shared_ptr<sge::gui::layouts::grid>()
			)
	),
	names_head(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,0)
			),
		SGE_TEXT("Name(s):")
	),
	score_head(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,0)
			),
		SGE_TEXT("Score:")
	),
	names_text(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,1)
			),
		sge::algorithm::join_strings(
			context<machine>().gameover_names(),
			SGE_TEXT(", ")
		)
	),
	score_text(
		score,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(1,1)
			),
		sge::lexical_cast<sge::string>(
			context<machine>().gameover_score()
		)
	),
	buttons_return(
		background_,
		sge::gui::widgets::parameters()
			.pos(	
				sge::gui::point(0,2)
			),
		SGE_TEXT("Main menu")
	),
	return_connection(
		buttons_return.register_clicked(
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
	tick_event const &)
{
	context<machine>().dispatch();
	m_.update();
	m_.draw();
	return discard_event();
}

boost::statechart::result
sanguis::client::states::gameover::react(
	menu_event const &)
{
	return transit<menu>();
}


boost::statechart::result
sanguis::client::states::gameover::react(
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		std::tr1::bind(
			&gameover::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result sanguis::client::states::gameover::handle_default_msg(
	messages::base const &)
{
	return discard_event();
}

void sanguis::client::states::gameover::return_clicked()
{
	post_event(
		menu_event());
}
