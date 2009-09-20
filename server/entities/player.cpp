#include "player.hpp"
#include "base_parameters.hpp"
#include "../perks/perk.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
#include "../environment/load_context.hpp"
#include "../level_calculate.hpp"
#include "../auras/update_sight.hpp"
#include <sge/text.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/bind.hpp>

sanguis::server::entities::player::player(
	server::environment::load_context_ptr const load_context_,
	damage::armor const &armor,
	property_map const &properties,
	string const &name_,
	server::player_id const player_id_
)
:
	entity_with_weapon(
		base_parameters(
			load_context_,
			armor,
			team::players,
			properties,
			entity_type::player,
			false,
			load_context_->entity_dim(
				SGE_TEXT("player")
			)
		),
		weapons::auto_ptr()
	),
	name_(name_),
	player_id_(player_id_),
	exp_(static_cast<exp_type>(0)),
	level_(static_cast<level_type>(0)),
	level_delta_(static_cast<level_type>(0)),
	skill_points_(0)
{
	auras::auto_ptr new_aura(
		sge::make_auto_ptr<
			auras::update_sight
		>(
			1000, // FIXME
			boost::bind(
				&player::update_sight_range,
				this,
				_1
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

void
sanguis::server::entities::player::exp(
	exp_type const e
)
{
	exp_ = e;
	level_type const
		old_level = level(),
		new_level = level_calculate(exp(), old_level);

	if (new_level > old_level)
	{
		level_delta_ += new_level - old_level;
		level_ = new_level;
		++skill_points_;

		/*
		environment()->level_up()(
			*this,
			old_level
		);
		*/
	}
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

sanguis::server::level_type
sanguis::server::entities::player::level_delta() const
{
	return level_delta_;
}

bool
sanguis::server::entities::player::perk_choosable(
	perk_type::type const p) const
{
	return skill_points_
		&& perk_tree_.choosable(
			p,
			level()
		)
		&& entity::perk_choosable(p);
}

void
sanguis::server::entities::player::add_perk(
	perks::auto_ptr p)
{
	perk_tree_.take(
		p->type()
	);

	entity::add_perk(
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
			!entity::perk_choosable(
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
sanguis::server::entities::player::update_sight_range(
	entity_id const entity_id_
)
{
	environment()->update_sight_range(
		player_id(),
		entity_id_
	);
}

