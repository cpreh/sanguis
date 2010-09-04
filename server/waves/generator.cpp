#include "generator.hpp"
#include "infinite.hpp"
#include "single.hpp"
#include "make.hpp"
#include "convert_enemy_name.hpp"
#include "../console.hpp"
#include "../net_id_from_args.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/exception.hpp>
#include <boost/assign/ptr_list_inserter.hpp>

#include "../log.hpp"
#include <fcppt/log/headers.hpp>
#include <fcppt/lexical_cast.hpp>

// NOTE: be careful when we move this class because
// it should not register the functions more than once

sanguis::server::waves::generator::generator(
	server::console &_console
)
:
	console_(_console),
	spawn_connection_(
		console_.insert(
			FCPPT_TEXT("spawn"),
			std::tr1::bind(
				&generator::spawn,
				this,
				std::tr1::placeholders::_1
			),
			FCPPT_TEXT("spawn wave (wavename) [count], spawn enemy (enemyname) [count] or spawn all")
		)
	),
	waves_()
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
		wave_list::iterator it = waves_.begin();
		it != waves_.end();
	)
	{
		it->process(
			diff,
			env,
			load_context
		);

		if(it->ended())
			it = waves_.erase(it);
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
		args_.size() == 3u
		&& args_[1] == FCPPT_TEXT("all")
	)
	{
		spawn_all();

		return;
	}

	if(
		args_.size() != 4u && args_.size() != 5u
	)
	{
		console_.print_line(
			server::net_id_from_args(
				args_
			),
			FCPPT_TEXT("Invalid parameter count for spawn command.")
		);

		return;
	}

	fcppt::string const action(
		args_[1]
	);

	unsigned const count(
		args_.size() == 5u
		?
			fcppt::lexical_cast<
				unsigned
			>(
				args_[3]
			)
		:
			1u
	);
	
	if(
		action == FCPPT_TEXT("wave")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				make(
					args_[2]
				)
			);
	else if(
		action == FCPPT_TEXT("enemy")
	)
		for(
			unsigned i = 0;
			i < count;
			++i
		)
			fcppt::container::ptr::push_back_unique_ptr(
				waves_,
				fcppt::make_unique_ptr<
					single
				>(
					convert_enemy_name(
						args_[2]
					)
				)
			);
	else
	{
		console_.print_line(
			server::net_id_from_args(
				args_
			),
			FCPPT_TEXT("Invalid argument for spawn command.")
		);
	}
}
catch(
	fcppt::exception const &e
)
{
	console_.print_line(
		server::net_id_from_args(
			args_
		),
		e.string()
	);
}

void
sanguis::server::waves::generator::spawn_all()
{
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves_)
	(
		delay(60),
		spawn_interval(40),
		spawns_per_wave(5),
		enemy_type::spider
	)(
		delay(0),
		spawn_interval(9),
		spawns_per_wave(15),
		enemy_type::maggot
	)(
		delay(50),
		spawn_interval(20),
		spawns_per_wave(10),
		enemy_type::maggot
	)(
		delay(0),
		spawn_interval(30),
		spawns_per_wave(8),
		enemy_type::zombie01
	)(
		delay(0),
		spawn_interval(30),
		spawns_per_wave(8),
		enemy_type::zombie01
	)(
		delay(90),
		spawn_interval(60),
		spawns_per_wave(7),
		enemy_type::zombie00
	)(
		delay(45),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_brown
	)(
		delay(80),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_white
	)(
		delay(120),
		spawn_interval(30),
		spawns_per_wave(3),
		enemy_type::wolf_black
	)(
		delay(130),
		spawn_interval(80),
		spawns_per_wave(6),
		enemy_type::spider
	)(
		delay(180),
		spawn_interval(120),
		spawns_per_wave(3),
		enemy_type::skeleton
	);
}
