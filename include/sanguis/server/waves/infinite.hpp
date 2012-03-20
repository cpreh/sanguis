#ifndef SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED

#include <sanguis/server/waves/wave.hpp>
#include <sanguis/server/waves/delay.hpp>
#include <sanguis/server/waves/spawn_interval.hpp>
#include <sanguis/server/waves/spawns_per_wave.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class infinite
:
	public wave
{
	FCPPT_NONCOPYABLE(
		infinite
	);
public:
	infinite(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		waves::delay,
		waves::spawn_interval,
		waves::spawns_per_wave,
		enemy_type::type
	);

	~infinite();
private:
	void
	process(
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::diff_timer delay_timer_;

	spawn_interval const spawn_interval_;

	spawns_per_wave const spawns_per_wave_;

	enemy_type::type const etype_;
};

}
}
}

#endif
