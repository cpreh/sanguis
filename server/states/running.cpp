#include "running.hpp"
#include "unpaused.hpp"
#include "../collision/test.hpp"
#include "../collision/execute.hpp"
#include "../add_decorations.hpp"
#include "../create_player.hpp"
#include "../environment.hpp"
#include "../message_functor.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../message_convert/level_up.hpp"
#include "../message_convert/experience.hpp"
#include "../perks/factory.hpp"
#include "../perks/perk.hpp"
#include "../log.hpp"
#include "../send_available_perks.hpp"
#include "../cheat.hpp"
#include "../player_record.hpp"
#include "../../connect_state.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/highscore.hpp"
#include "../../messages/create.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/log/headers.hpp>
#include <sge/collision/world.hpp>
#include <sge/utf8/convert.hpp>
#include <sge/text.hpp>
#include <sge/type_info.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/tr1/random.hpp>
#include <algorithm>
#include <ostream>

sanguis::server::states::running::running(
	my_context ctx
)
:
	my_base(ctx),
	//players_(),
	//wave_generator(),
	//player_records()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor, listening")
	);

	context<machine>().listen();
}

sanguis::server::states::running::~running()
{}

#if 0
void
sanguis::server::states::running::update_waves(
	time_type const time
)
{
	/*
	wave_generator.process(
		time,
		environment()
	);
	*/
}
#endif

void
sanguis::server::states::running::add_player_record(
	player_record const &rec
)
{
	/*
	player_records.push_back(
		rec
	);
	*/
}

void
sanguis::server::states::running::all_dead()
{
	/*
	messages::types::string_vector names;
	exp_type exp(0);

	BOOST_FOREACH(
		player_record_vector::const_reference ref,
		player_records
	)
	{
		names.push_back(
			sge::utf8::convert(
				ref.name()
			)
		);

		exp = std::max(
			exp,
			ref.exp()
		);
	}

	send()(
		messages::create(
			messages::highscore
			(
				names,
				exp
			)
		)
	);

	player_records.clear();
	*/
}

boost::statechart::result
sanguis::server::states::running::react(
	message_event const &m
)
{
	message_functor<
		running,
		boost::statechart::result
	> mf(
		*this,
		m.id()
	);

	return messages::unwrap<
		boost::mpl::vector<
			messages::client_info,
			messages::connect,
			messages::disconnect,
			messages::player_cheat,
			messages::player_choose_perk
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
		boost::bind(
			&running::handle_default_msg,
			this,
			m.id(),
			_1
		)
	);
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const net_id,
	messages::client_info const &m
)
{
	global_context_->insert_player(
		0, // FIXME: which world id?
		net_id,
		sge::utf8::convert(
			m.get<
				messages::roles::name
			>()
		),
		state_cast<
			unpaused const *
		>()
		?
			connect_state::unpaused
		:
			connect_state::paused
	);

	return discard_event();
}

sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::connect const &
)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("client ")
			<< id
			<< SGE_TEXT(" connected")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::disconnect const &)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("client with id ")
			<< id
			<< SGE_TEXT(" disconnected")
	);

	global_context_->disconnect(
		id
	);

	//players()[id]->die();

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_cheat const &p)
{
	cheat(
		player(
			id
		),
		static_cast<
			cheat_type::type
		>(
			p.get<messages::roles::cheat>()
		),
		environment()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_choose_perk const &p
)
{
	global_context_->choose_perk(
		id,
		// FIXME: sanitize the input!
		static_cast<
			perk_type::type
		>(
			p.get<
				messages::role::perk
			>()
		)
	);

	return discard_event();

}

void sanguis::server::states::running::level_callback(
	entities::player &p,
	level_type)
{
	send()(message_convert::level_up(p));

	send_available_perks(
		p
	);
}

void sanguis::server::states::running::send_available_perks(
	entities::player const &p)
{
	server::send_available_perks(
		p,
		context<machine>().unicast(
			p.net_id()
		)
	);
}

boost::statechart::result
sanguis::server::states::running::handle_default_msg(
	net::id_type const id,
	messages::base const &m
)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("received unexpected message from id ")
			<< id
			<< SGE_TEXT(" of type ")
			<< sge::type_info(typeid(m)).name());

	return discard_event();
}

sge::log::logger &
sanguis::server::states::running::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("running: "),
		true
	);
	return log_;
}
