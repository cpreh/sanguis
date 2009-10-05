#include "player.hpp"
#include "property/initial.hpp"
#include "../perks/perk.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
#include "../environment/load_context.hpp"
#include "../level_calculate.hpp"
#include "../auras/update_sight.hpp"
#include "../../messages/add.hpp"
#include "../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/text.hpp>
#include <sge/make_auto_ptr.hpp>
#include <tr1/functional>

sanguis::server::entities::player::player(
	server::environment::load_context_ptr const load_context_,
	entities::health_type const health_,
	damage::armor const &armor_,
	entities::movement_speed const speed_,
	string const &name_,
	server::player_id const player_id_
)
:
	base(),
	movable(
		property::initial(
			speed_,
			0
		),
		static_cast<space_unit>(0)
	),
	with_auras(),
	with_buffs(),
	with_dim(
		load_context_->entity_dim(
			SGE_TEXT("player")
		)
	),
	with_health(
		health_,
		armor_
	),
	with_perks(),
	with_weapon(
		weapons::auto_ptr()
	),
	name_(name_),
	player_id_(player_id_),
	exp_(0),
	level_(0),
	skill_points_(0)
{
	auras::auto_ptr new_aura(
		sge::make_auto_ptr<
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
	);

	add_aura(
		new_aura
	);
}

sanguis::server::exp_type
sanguis::server::entities::player::exp() const
{
	return exp_;
}

bool
sanguis::server::entities::player::add_exp(
	exp_type const e
)
{
	exp_ += e;

	level_type const
		old_level(
			level()
		),
		new_level(
			level_calculate(
				exp(),
				old_level
			)
		);

	if (new_level == old_level)
		return false;
	
	skill_points_ += new_level - old_level;

	level_ = new_level;
	
	return true;
}

sanguis::server::string const
sanguis::server::entities::player::name() const
{
	return name_;
}

sanguis::server::level_type
sanguis::server::entities::player::level() const
{
	return level_;
}

bool
sanguis::server::entities::player::perk_choosable(
	perk_type::type const p
) const
{
	return skill_points_
		&& perk_tree_.choosable(
			p,
			level()
		)
		&& with_perks::perk_choosable(p);
}

void
sanguis::server::entities::player::add_perk(
	perks::auto_ptr p
)
{
	perk_tree_.take(
		p->type()
	);

	with_perks::add_perk(
		p
	);

	--skill_points_;
}

sanguis::server::perks::list const
sanguis::server::entities::player::available_perks() const
{
	perks::list ret(
		perk_tree_.choosables(
			level()
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
	entity_id const entity_id_
)
{
	environment()->add_sight_range(
		player_id(),
		entity_id_
	);
}

void
sanguis::server::entities::player::remove_sight_range(
	entity_id const entity_id_
)
{
	environment()->remove_sight_range(
		player_id(),
		entity_id_
	);
}

void
sanguis::server::entities::player::on_update(
	time_type const time_
)
{
	with_buffs::on_update(
		time_
	);

	with_health::on_update(
		time_
	);

	with_perks::on_update(
		time_
	);

	with_weapon::on_update(
		time_
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::player::add_message() const
{
	return messages::create(
		messages::add(
			id(),
			pos(),
			angle(),
			abs_speed(),
			current_health(),
			max_health(),
			dim(),
			type()
		)
	);
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
	weapon_type::type const type_
)
{
	environment()->got_weapon(
		player_id(),
		id(),
		type_
	);
}
