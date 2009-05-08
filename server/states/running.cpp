#include "running.hpp"
#include "unpaused.hpp"
#include "../entities/property.hpp"
#include "../collision/satellite.hpp"
#include "../collision/base.hpp"
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
#include "../../connect_state.hpp"
#include "../../messages/unwrap.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/log/headers.hpp>
#include <sge/collision/satellite.hpp>
#include <sge/collision/world.hpp>
#include <sge/utf8/convert.hpp>
#include <sge/text.hpp>
#include <sge/type_info.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/tr1/random.hpp>
#include <ostream>

sanguis::server::states::running::running(
	my_context ctx)
:
	my_base(ctx),
	environment_(
		boost::bind(
			&server::machine::send,
			&(context<machine>()),
			_1
		),
		boost::bind(&running::insert_entity, this, _1),
		boost::bind(&running::divide_exp, this, _1),
		boost::bind(&running::level_callback, this, _1, _2),
		boost::bind(&running::load_callback, this),
		boost::bind(&pickup_spawner::spawn, &pickup_spawner_, _1),
		boost::bind(&running::pickup_chance, this, _1),
		context<machine>().collision()
	),
	coll_connection(
		context<machine>().collision()->register_callback(
			boost::bind(
				&running::collision,
				this,
				_1,
				_2
			)
		)
	),
	console_print(
		boost::bind(
			&server::machine::console_print,
			&(context<machine>()),
			_1
		)
	),
	entities_(),
	players_(),
	pickup_spawner_(
		environment()
	),
	pickup_chance_(
		sge::random::make_inclusive_range(
			static_cast<probability_type>(0),
			static_cast<probability_type>(1)
		)
	),
	wave_generator()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor, listening")
	);

	context<machine>().listen();

	add_decorations(
		environment()
	);

	context<machine>().collision()->test_callback(
		boost::bind(
			&running::collision_test,
			this,
			_1,
			_2
		)
	);
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
	
	send()(ref.add_message());

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
	return *players()[id];
}

void sanguis::server::states::running::divide_exp(
	exp_type const exp)
{
	if (exp == static_cast<exp_type>(0))
		return;

	BOOST_FOREACH(running::player_map::reference ref, players())
	{
		entities::player &p = *ref.second;
		p.exp(p.exp() + exp);

		send()(message_convert::experience(p));
	}
}

void sanguis::server::states::running::level_callback(
	entities::player &p,
	level_type)
{
	send()(message_convert::level_up(p));
}

bool sanguis::server::states::running::collision_test(
	sge::collision::satellite const &a,
	sge::collision::satellite const &b)
{
	collision::base const
		&e0(
			dynamic_cast<
				collision::satellite const &
			>(a).base()
		),
	        &e1(
			dynamic_cast<
				collision::satellite const &
			>(b).base()
		);
	
	return e0.can_collide_with(e1) || e1.can_collide_with(e0);
}

void sanguis::server::states::running::collision(
	sge::collision::satellite &a,
	sge::collision::satellite &b)
{
	collision::base
		&e0(
			dynamic_cast<
				collision::satellite &
			>(a).base()
		),
		&e1(
			dynamic_cast<
				collision::satellite &
			>(b).base()
		);
	
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
		environment()
	);
}

sanguis::server::environment const &
sanguis::server::states::running::environment() const
{
	return environment_;
}

boost::statechart::result
sanguis::server::states::running::react(
	message_event const &m)
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
	messages::client_info const &m)
{
	players().insert(
		net_id,
		create_player(
			m,
			context<machine>().unicast(
				net_id
			),
			environment(),
			entities_,
			state_cast<unpaused const *>()
				? connect_state::unpaused
				: connect_state::paused
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::connect const &)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("client ")
			<< id
			<< SGE_TEXT(" connected"));
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
			<< SGE_TEXT(" disconnected"));

	players()[id]->die();

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
			p.get<messages::roles::perk>()
		)
	);
	
	entities::player &player_(
		player(id)
	);
	
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
			perk
		)
	);
	
	send_available_perks(
		player_,
		context<machine>().unicast(
			id
		)
	);
	
	return discard_event();
}

sanguis::server::send_callback const &
sanguis::server::states::running::send() const
{
	return environment().send();
}

bool
sanguis::server::states::running::pickup_chance(
	probability_type const p)
{
	return pickup_chance_() <= p;
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
