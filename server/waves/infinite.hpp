#ifndef SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED

#include "wave.hpp"
#include "delay.hpp"
#include "spawn_interval.hpp"
#include "count.hpp"
#include "spawns_per_wave.hpp"
#include "../../time_type.hpp"
#include "../../enemy_type.hpp"
#include <sge/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class infinite : public wave {
public:
	infinite(
		waves::delay,
		waves::spawn_interval,
		waves::count,
		waves::spawns_per_wave,
		enemy_type::type
	);
	
	~infinite();
private:
	void
	process(
		time_type diff,
		environment::object_ptr,
		environment::load_context_ptr
	);
	
	bool ended() const;

	time_type 
		delay_,
		spawn_interval_;
	unsigned 
		count_,
		spawns_per_wave_;
	enemy_type::type const etype_;

	sge::scoped_ptr<
		wave
	> simple_;
};

}
}
}

#endif
