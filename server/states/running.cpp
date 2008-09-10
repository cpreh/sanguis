#include "running.hpp"
#include "waiting.hpp"
#include "../environment.hpp"
#include "../damage_types.hpp"
#include "../message_functor.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../weapons/factory.hpp"
#include "../log.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/level_up.hpp"
#include "../../resolution.hpp"
#include "../../dispatch_type.hpp"
#include "../../log_headers.hpp"
#include <sge/iconv.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <ostream>

sanguis::server::states::running::running(my_context ctx)
: my_base(ctx),
  send(boost::bind(&server::machine::send,&(context<machine>()),_1)),
  console_print(boost::bind(&server::machine::console_print,&(context<machine>()),_1)),
  wave_generator()
{
	for (int i = 0; i < 10; ++i)
	{
		// TODO: generate decos here
	}
}

sanguis::server::entities::container &
sanguis::server::states::running::entities()
{
	return entities_;
}

sanguis::server::entities::container const &
sanguis::server::states::running::entities() const
{
	return entities_;
}

sanguis::server::entities::entity &
sanguis::server::states::running::insert_entity(
	entities::auto_ptr e)
{
	entities_.push_back(e);
	entities::entity &ref = entities_.back();
	ref.update(time_type(),entities_);

	if(ref.type() == entity_type::indeterminate)
		return ref;
	
	// TODO: sanity check the message (needs smart pointer as well)
	send(ref.add_message());

	return ref;
}

sanguis::server::states::running::player_map &
sanguis::server::states::running::players()
{
	return players_;
}

sanguis::server::states::running::player_map const &
sanguis::server::states::running::players() const
{
	return players_;
}

void sanguis::server::states::running::divide_exp(
	messages::exp_type const exp)
{
	if (exp == static_cast<messages::exp_type>(0))
		return;

	BOOST_FOREACH(running::player_map::reference ref, players())
	{
		entities::player &p = *ref.second;
		p.exp(p.exp() + exp);

		send(
			messages::auto_ptr(
				new messages::experience(
					p.id(),
					p.exp())));
	}
}

void sanguis::server::states::running::level_callback(
	entities::player &p,
	messages::level_type)
{
	// no message_converter here because it operates on a _specific_ entity type
	send(
		messages::auto_ptr(
			new messages::level_up(
				p.id(),
				p.level())));
}

void sanguis::server::states::running::process(
	time_type const time)
{
	wave_generator.process(
		time,
		get_environment());
}

sanguis::server::environment const
sanguis::server::states::running::get_environment()
{
	return environment(
		send,
		boost::bind(&running::insert_entity, this, _1),
		boost::bind(&running::divide_exp, this, _1),
		boost::bind(&running::level_callback, this, _1, _2));
}

boost::statechart::result
sanguis::server::states::running::react(
	message_event const &m)
{
	message_functor<running, boost::statechart::result> mf(
		*this,
		m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::client_info,
			messages::connect
		>,
		boost::statechart::result>(
			mf,
			*m.message,
			boost::bind(&running::handle_default_msg, this, m.id, _1));
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const net_id,
	messages::client_info const &m)
{
	// TODO: this should be cleaned up somehow
	// 1) create the player
	// 2) tell the client the player's id _before_ doing anything else
	// 3) add the player
	entities::auto_ptr new_player(
		new entities::player(
			get_environment(),
			damage::list(messages::mu(0)),
			net_id,
			messages::pos_type(
				messages::mu(resolution().w()/2),
				messages::mu(resolution().h()/2)),
			messages::mu(0),
			messages::mu(0),
			boost::assign::map_list_of
				(entities::property::type::health,
				entities::property(messages::mu(100)))
				(entities::property::type::movement_speed,
				entities::property(messages::mu(0),messages::mu(100))),
			m.name()));

	players()[net_id] = dynamic_cast<entities::player *>(
		new_player.get());

	context<machine>().send(
		messages::auto_ptr(
			new messages::assign_id(
				new_player->id())),
		net_id);

	entities::player &p(
		dynamic_cast<entities::player &>(
			insert_entity(
				new_player)));

	// TODO: some defaults here
	p.add_weapon(
		weapons::create(
			weapon_type::melee,
			get_environment()));
	p.add_weapon(
		weapons::create(
			weapon_type::pistol,
			get_environment()));

	// send start experience
	// no message_converter here because it operates on a _specific_ entity type
	send(
		messages::auto_ptr(
			new messages::experience(
				p.id(),
				p.exp())));
	send(
		messages::auto_ptr(
			new messages::level_up(
				p.id(),
				p.level())));

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type,
	messages::connect const &)
{
	
	// FIXME
	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::handle_default_msg(
	net::id_type const id,
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: running: received unexpected message from id ")
			<< id
			<< SGE_TEXT(" of type ")
			<< sge::iconv(typeid(m).name()));

	return discard_event();
}

sge::log::logger &
sanguis::server::states::running::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("running: "));
	return log_;
}
