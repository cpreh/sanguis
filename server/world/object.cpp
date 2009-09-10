#include "object.hpp"
#include <sge/collision/system_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

sanguis::server::world::object::object(
	sge::collision::system_ptr const sys
)
:
	collision_world_(
		sys->create_world(
			// TODO
		)
	),
	entities_(),
	props_(),
	coll_connection(
		collision_world_->register_callback(
			boost::bind(
				collision::execute,
				_1,
				_2
			)
		)
	)
{}

sanguis::server::world::object::~object()
{}

void
sanguis::server::world::object::update(
	time_type const time_
)
{
	if(
		sight_range_timer.update()
	)
		BOOST_FOREACH(
			sigth_range_map::reference sight_range_,
			sigth_ranges_
		)
			sight_range_.update();
	
	BOOST_FOREACH(
		entities::container::reference entity_,
		entities_
	)
		entity_.update(
			time_,
			entities_
		);
}

void
sanguis::server::world::object::transfer(
	sever::entities::entity_auto_ptr entity_
)
{
	entity_->environment(
		environment_
	);

	insert_entity(
		entity_
	);
}

void
sanguis::server::world::weapon_changed(
	entity_id id,
	weapon_type::type
)
{
	
}

void
sanguis::server::world::got_weapon(
	entity_id id,
	weapon_type::type
)
{
	global_context_->
}

void
sanguis::server::world::attacking_changed(
	entity_id const id,
	bool const is_attacking
)
{
	send_entity_specific(
		id,
		is_attacking
		?
			messages::create(
				messages::start_attacking(
					id
				)
			)
		:
			messages::create(
				messages::stop_attacking(
					id
				)
			)
	);
}

void
sanguis::server::world::reloading_changed(
	entity_id const id,
	bool const is_reloading
)
{
	send_entity_specific(
		id,
		is_reloading
		?
			messages::create(
				messages::start_reloading(
					id
				)
			)
		:
			messages::create(
				messages::stop_reloading(
					id
				)
			)
	);
}

void
sanguis::server::world::max_health_changed(
	entity_id const id,
	health_type const health_
)
{
	send(
		id,
		messages::create(
			messages::max_health(
				id,
				health_
			)
		)
	);
}

void
sanguis::server::world::object::request_transfer(
	world_id const world_id_,
	entity_id const entity_id_
)
{
	global_context_->transfer_entity(
		world_id_,
		entities_.release(
			std::find_if(
				entities_.begin(),
				entities_.end(),
				id_equal(
					entity_id_
				)
			)
		)
	);
}
void
sanguis::server::world::update_sight_range(
	net::id_type const player_id,
	entity_id const target_id
)
{
	sight_ranges[
		player_id
	].insert(
		target_id
	);
}

sanguis::server::entities::entity &
sanguis::server::world::object::insert_entity(
	entities::auto_ptr e
)
{
	entities_.push_back(e);
	return entities.back();
	//entities::entity &ref = entities_.back();

	//if(ref.type() == entity_type::indeterminate)
	//	return ref;
	
	//send()(ref.add_message());

//	return ref;
}

void
sanguis::server::world::object::send_entity_specific(
	entity_id const id,
	messages::auto_ptr msg
)
{
	BOOST_FOREACH(
		sight_range_list::const_reference range,
		sight_ranges
	)
		if(
			range.contains(
				range
			)
		)
			global_context_->send(
				range.player_id(),
				msg
			);
}
