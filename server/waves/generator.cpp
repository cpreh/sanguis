#include "generator.hpp"
#include "infinite.hpp"
#include "single.hpp"
#include "make.hpp"
#include "convert_enemy_name.hpp"
#include "../../exception.hpp"
//#include "debug.hpp"
#include <sge/console/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <boost/assign/ptr_list_inserter.hpp>

sanguis::server::waves::generator::generator(
	sge::console::object &console_
)
:
	spawn_connection(
		console_.insert(
			FCPPT_TEXT("spawn"),
			std::tr1::bind(
				&generator::spawn,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("spawn wave [wavename] or spawn enemy [enemyname]")
		)
	)
{
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves)
	(
		delay(60),
		spawn_interval(2),
		count(15),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(0),
		spawn_interval(2),
		count(20),
		spawns_per_wave(2),
		enemy_type::maggot
	)(
		delay(0),
		spawn_interval(1.5f),
		count(40),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(0),
		spawn_interval(2),
		count(60),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(90),
		spawn_interval(1),
		count(8),
		spawns_per_wave(2),
		enemy_type::zombie00
	)(
		delay(45),
		spawn_interval(1),
		count(8),
		spawns_per_wave(1),
		enemy_type::wolf_brown
	)(
		delay(80),
		spawn_interval(1),
		count(6),
		spawns_per_wave(2),
		enemy_type::wolf_white
	)(
		delay(120),
		spawn_interval(1),
		count(6),
		spawns_per_wave(2),
		enemy_type::wolf_black
	)(
		delay(130),
		spawn_interval(.5f),
		count(10),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(180),
		spawn_interval(1),
		count(3),
		spawns_per_wave(1),
		enemy_type::skeleton
	);

	//boost::assign::ptr_push_back<waves::debug>(waves)
	//();
}

sanguis::server::waves::generator::~generator()
{}

void
sanguis::server::waves::generator::process(
	time_type const diff,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context
)
{
	for(
		wave_list::iterator it = waves.begin();
		it != waves.end();
	)
	{
		it->process(
			diff,
			env,
			load_context
		);

		if(it->ended())
			it = waves.erase(it);
		else
			++it;
	}
}

void
sanguis::server::waves::generator::spawn(
	sge::console::arg_list const &args_
)
try
{
	if(
		args_.size() != 2u
	)
	{
		// TODO: error!
		return;
	}

	fcppt::string const action(
		args_[0]
	);

	if(
		action == FCPPT_TEXT("wave")
	)
		waves.push_back(
			make(
				args_[1]
			)
		);
	else if(
		action == FCPPT_TEXT("enemy")
	)
	{
		wave_auto_ptr ptr(
			fcppt::make_auto_ptr<
				single
			>(
				convert_enemy_name(
					args_[1]
				)
			)
		);

		waves.push_back(
			ptr
		);
	}
	else
	{
		// TODO: error!
	}
}
catch(
	exception const &e
)
{
	// TODO: error!
}
