#include "generator.hpp"
#include "infinite.hpp"
#include "single.hpp"
#include "make.hpp"
#include "convert_enemy_name.hpp"
#include "../../exception.hpp"
#include <sge/console/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <boost/assign/ptr_list_inserter.hpp>

#include "../log.hpp"
#include <fcppt/log/headers.hpp>

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
			FCPPT_TEXT("spawn wave [wavename], spawn enemy [enemyname] or spawn all")
		)
	)
{}

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
		args_.size() == 2u
		&& args_[1] == FCPPT_TEXT("all")
	)
	{
		spawn_all();

		return;
	}

	if(
		args_.size() != 3u
	)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Invalid call to spawn!")
		);

		// TODO: error!
		return;
	}

	fcppt::string const action(
		args_[1]
	);

	if(
		action == FCPPT_TEXT("wave")
	)
		waves.push_back(
			make(
				args_[2]
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
					args_[2]
				)
			)
		);

		waves.push_back(
			ptr
		);
	}
	else
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Invalid argument")
		);
		// TODO: error!
	}
}
catch(
	exception const &e
)
{
	FCPPT_LOG_ERROR(
		log(),
		fcppt::log::_
			<< e.string()
	);
	// TODO: error!
}

void
sanguis::server::waves::generator::spawn_all()
{
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves)
	(
		delay(60),
		spawn_interval(2),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(0),
		spawn_interval(2),
		spawns_per_wave(2),
		enemy_type::maggot
	)(
		delay(0),
		spawn_interval(1.5f),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(0),
		spawn_interval(2),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(90),
		spawn_interval(1),
		spawns_per_wave(2),
		enemy_type::zombie00
	)(
		delay(45),
		spawn_interval(1),
		spawns_per_wave(1),
		enemy_type::wolf_brown
	)(
		delay(80),
		spawn_interval(1),
		spawns_per_wave(2),
		enemy_type::wolf_white
	)(
		delay(120),
		spawn_interval(1),
		spawns_per_wave(2),
		enemy_type::wolf_black
	)(
		delay(130),
		spawn_interval(.5f),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(180),
		spawn_interval(1),
		spawns_per_wave(1),
		enemy_type::skeleton
	);
}
