#include "running.hpp"
#include "waiting.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/level_up.hpp"
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <ostream>

sanguis::server::states::running::running(my_context ctx)
	: my_base(ctx),
		send(boost::bind(&server::machine::send,&(context<machine>()),_1)),
		console_print(boost::bind(&server::machine::console_print,&(context<machine>()),_1)),
		enemy_timer_(SGE_TEXT("enemy_timer"),sge::su(2))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

sge::time::timer &sanguis::server::states::running::enemy_timer()
{
	return enemy_timer_.v();
}

sanguis::server::entities::container &sanguis::server::states::running::entities()
{
	return entities_;
}

const sanguis::server::entities::container &sanguis::server::states::running::entities() const
{
	return entities_;
}

sanguis::server::entities::entity &sanguis::server::states::running::insert_entity(entities::auto_ptr e)
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

sanguis::server::states::running::player_map &sanguis::server::states::running::players()
{
	return players_;
}

sanguis::server::states::running::player_map const &sanguis::server::states::running::players() const
{
	return players_;
}

void sanguis::server::states::running::divide_exp(const messages::exp_type exp)
{
	if (exp == static_cast<messages::exp_type>(0))
		return;

	BOOST_FOREACH(running::player_map::reference ref, context<running>().players())
	{
		entities::player &p = *ref.second;
		p.exp(p.exp() + exp);
		context<running>().send(
			messages::auto_ptr(
				new messages::experience(
					p.id(),
					p.exp())));
	}
}

void sanguis::server::states::running::level_callback(entities::player &p,const messages::level_type)
{
	// no message_converter here because it operates on a _specific_ entity type
	context<running>().send(
		messages::auto_ptr(
			new messages::level_up(
				p.id(),
				p.level())));
}
