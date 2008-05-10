#include "running.hpp"
#include "waiting.hpp"
#include "../entities/entity.hpp"
#include "../message_converter.hpp"

#include <sge/iostream.hpp>
#include <ostream>

#include <boost/bind.hpp>

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

	if (ref.type() != entity_type::indeterminate)
		send(message_convert<messages::add>(ref));
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
