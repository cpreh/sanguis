#include "player.hpp"
#include "property/initial.hpp"
#include "../perks/perk.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
#include "../environment/load_context.hpp"
#include "../level_calculate.hpp"
#include "../auras/update_sight.hpp"
#include "../../messages/add_player.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::player::player(
	server::environment::load_context_ptr const _load_context,
	entities::health_type const _health,
	damage::armor const &_armor,
	entities::movement_speed const _speed,
	string const &_name,
	server::player_id const _player_id
)
:
	base(),
	movable(
		property::initial(
			_speed.get(),
			0
		),
		static_cast<space_unit>(0)
	),
	with_auras(),
	with_buffs(),
	with_dim(
		_load_context->entity_dim(
			FCPPT_TEXT("player")
		)
	),
	with_health(
		_health,
		_armor
	),
	with_perks(),
	with_weapon(
		weapons::unique_ptr()
	),
	name_(_name),
	player_id_(_player_id),
	exp_(0),
	level_(0),
	skill_points_(0)
{
	add_aura(
		auras::unique_ptr(
			fcppt::make_unique_ptr<
				auras::update_sight
			>(
				1000, // FIXME
				std::tr1::bind(
					&player::add_sight_range,
					this,
					std::tr1::placeholders::_1
				),
				std::tr1::bind(
					&player::remove_sight_range,
					this,
					std::tr1::placeholders::_1
				)
			)
		)	
	);
}

void
sanguis::server::entities::player::add_exp(
	exp_type const _exp
)
{
	exp_ =
		server::exp_type(
			exp_.get()
			+ _exp.get()
		);

	environment()->exp_changed(
		player_id(),
		id(),
		exp_
	);

	level_type const
		old_level(
			level_
		),
		new_level(
			server::level_calculate(
				exp_,
				old_level
			)
		);

	if(
		new_level == old_level
	)
		return;
	
	skill_points_ += new_level.get() - old_level.get();

	level_ = new_level;

	environment()->level_changed(
		player_id(),
		id(),
		level_
	);
}

sanguis::server::string const
sanguis::server::entities::player::name() const
{
	return name_;
}

bool
sanguis::server::entities::player::perk_choosable(
	perk_type::type const _perk
) const
{
	return
		skill_points_
		&& perk_tree_.choosable(
			_perk,
			level_
		)
		&& with_perks::perk_choosable(
			_perk
		);
}

void
sanguis::server::entities::player::add_perk(
	perks::unique_ptr _ptr
)
{
	perk_tree_.take(
		_ptr->type()
	);

	with_perks::add_perk(
		move(
			_ptr
		)
	);

	--skill_points_;
}

sanguis::server::perks::list const
sanguis::server::entities::player::available_perks() const
{
	perks::list ret(
		perk_tree_.choosables(
			level_
		)
	);

	for(
		perks::list::iterator it = ret.begin();
		it != ret.end();
	)
		if(
			!with_perks::perk_choosable(
				*it
			)
		)
			it = ret.erase(it);
		else
			++it;
	
	return ret;
}

sanguis::server::player_id
sanguis::server::entities::player::player_id() const
{
	return player_id_;
}

void
sanguis::server::entities::player::on_die()
{
	environment()->remove_player(
		player_id()
	);
}

void
sanguis::server::entities::player::add_sight_range(
	entity_id const _entity_id
)
{
	environment()->add_sight_range(
		player_id(),
		_entity_id
	);
}

void
sanguis::server::entities::player::remove_sight_range(
	entity_id const _entity_id
)
{
	environment()->remove_sight_range(
		player_id(),
		_entity_id
	);
}

void
sanguis::server::entities::player::on_update(
	time_type const _time
)
{
	with_buffs::on_update(
		_time
	);

	with_health::on_update(
		_time
	);

	with_perks::on_update(
		_time
	);

	with_weapon::on_update(
		_time
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::player::add_message(
	server::player_id const _receiver
) const
{
	return
		_receiver == player_id()
		?
			make_add_message<
				messages::add_own_player
			>()
		:
			make_add_message<
				messages::add_player
			>();
}
sanguis::entity_type::type
sanguis::server::entities::player::type() const
{
	return entity_type::player;
}

sanguis::server::team::type
sanguis::server::entities::player::team() const
{
	return server::team::players;
}

void
sanguis::server::entities::player::on_new_weapon(
	weapon_type::type const _type
)
{
	environment()->got_weapon(
		player_id(),
		id(),
		_type
	);
}

template<
	typename Message
>
sanguis::messages::auto_ptr
sanguis::server::entities::player::make_add_message() const
{
	return
		messages::create(
			Message(
				id(),
				pos(),
				angle(),
				dim(),
				abs_speed(),
				current_health(),
				max_health()
			)
		);
}
