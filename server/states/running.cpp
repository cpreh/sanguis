#include "running.hpp"
#include "waiting.hpp"
#include "../entities/sattelite.hpp"
#include "../entities/base_parameters.hpp"
#include "../entities/property.hpp"
#include "../environment.hpp"
#include "../damage_types.hpp"
#include "../message_functor.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/decoration.hpp"
#include "../weapons/factory.hpp"
#include "../perks/factory.hpp"
#include "../perks/perk.hpp"
#include "../log.hpp"
#include "../send_available_perks.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../resolution.hpp"
#include "../../dispatch_type.hpp"
#include "../../random.hpp"
#include "../../exception.hpp"
#include <sge/iconv.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/collision/satellite.hpp>
#include <sge/collision/world.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/tr1/random.hpp>
#include <ostream>

sanguis::server::states::running::running(my_context ctx)
:
	my_base(ctx),
	coll_connection(
		context<machine>().collision()->register_callback(
			boost::bind(&running::collision,this,_1,_2))),
	send(
		boost::bind(
			&server::machine::send,
			&(context<machine>()),
			_1)),
	console_print(
		boost::bind(
			&server::machine::console_print,
			&(context<machine>()),
			_1)),
	wave_generator()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor"));
	create_decorations();
	context<machine>().collision()->test_callback(
		boost::bind(&running::collision_test,this,_1,_2));
}

void sanguis::server::states::running::create_decorations()
{
	typedef std::tr1::uniform_real<
		messages::space_unit
	> uniform_su;

	typedef std::tr1::uniform_int<
		unsigned
	> uniform_int;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_su
	> rng_type;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_int
	> rng_int_type;

	rng_type rng_x(
		create_seeded_randgen(),
		uniform_su(
			messages::mu(0),
			messages::mu(resolution().w())
		));

	rng_type rng_y(
		create_seeded_randgen(),
		uniform_su(
			messages::mu(0),
			messages::mu(resolution().h())
		));

	rng_type rng_angle(
		create_seeded_randgen(),
		uniform_su(
			messages::mu(0),
			sge::math::twopi<messages::space_unit>()
		));

	rng_int_type rng_deco_type(
		create_seeded_randgen(),
		uniform_int(
			static_cast<unsigned>(0),
			static_cast<unsigned>(decoration_type::size-1)
		));

	for (unsigned i = 0; i < 10; ++i)
	{
		pos_type const position(rng_x(),rng_y());
		space_unit const angle = rng_angle();
		decoration_type::type type = static_cast<decoration_type::type>(rng_deco_type());

		SGE_LOG_DEBUG(
			log(),
			sge::log::_1
				<< SGE_TEXT("created decoration type ") << type 
				<< SGE_TEXT(", position: ") << position << SGE_TEXT(", angle: ")
				<< angle);
		
		entities_.push_back(
			entities::auto_ptr(
				new entities::decoration(
					environment(),
					position,
					angle,
					type)));

		entities_.back().update(time_type(),entities_);
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

	if(ref.type() == entity_type::indeterminate)
		return ref;
	
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

sanguis::server::entities::player &
sanguis::server::states::running::player(
	net::id_type const id)
{
	player_map::iterator const it(
		players().find(
			id));
	if(it == players().end())
		throw exception(
			SGE_TEXT("Player not found!"));
	return *it->second;
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

bool sanguis::server::states::running::collision_test(
	sge::collision::satellite const &a,
	sge::collision::satellite const &b)
{
	entities::entity const &e0 = 
		dynamic_cast<entities::satellite const &>(a).entity();
	entities::entity const &e1 = 
		dynamic_cast<entities::satellite const &>(b).entity();
	
	return e0.can_collide_with(e1) || e1.can_collide_with(e0);
}

void sanguis::server::states::running::collision(
	sge::collision::satellite &a,
	sge::collision::satellite &b)
{
	entities::entity &e0 = 
		dynamic_cast<entities::satellite &>(a).entity();
	entities::entity &e1 = 
		dynamic_cast<entities::satellite &>(b).entity();
	e0.collision(e1);
	e1.collision(e0);
}

sanguis::load::context const &
sanguis::server::states::running::load_callback() const
{
	return context<machine>().resources();
}

void sanguis::server::states::running::process(
	time_type const time)
{
	wave_generator.process(
		time,
		environment());
}

sanguis::server::environment const
sanguis::server::states::running::environment()
{
	return server::environment(
		send,
		boost::bind(&running::insert_entity, this, _1),
		boost::bind(&running::divide_exp, this, _1),
		boost::bind(&running::level_callback, this, _1, _2),
		boost::bind(&running::load_callback, this),
		context<machine>().collision());
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
			messages::connect,
			messages::player_choose_perk
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
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("sending player's id"));
	// TODO: this should be cleaned up somehow
	// 1) create the player
	// 2) tell the client the player's id _before_ doing anything else
	// 3) add the player
	entities::auto_ptr new_player(
		new entities::player(
			environment(),
			damage::list(messages::mu(0)),
			net_id,
			messages::pos_type(
				messages::mu(resolution().w()/2),
				messages::mu(resolution().h()/2)),
			messages::mu(0),
			messages::mu(0),
			boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(messages::mu(100)))
				(entities::property_type::movement_speed,
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
			weapon_type::pistol,
			environment()));

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
	
	send_available_perks(
		p,
		send);

	BOOST_FOREACH(entities::entity &e,entities_)
	{
		if (e.id() == p.id())
			continue;

		send(e.add_message());
	}


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
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_choose_perk const &p)
{
	perk_type::type const perk(
		static_cast<
			perk_type::type
		>(
			p.perk()));
	
	entities::player &player_(
		player(id));
	
	if(!player_.perk_choosable(perk))
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("Player with id ")
				<< id
				<< SGE_TEXT(" tried to take an invalid perk")
				<< SGE_TEXT(" or has no skillpoints left!"));
		return discard_event();
	}

	player_.add_perk(
		perks::create(
			perk));
	
	send_available_perks(
		player_,
		send);
	
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
			<< SGE_TEXT("received unexpected message from id ")
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
