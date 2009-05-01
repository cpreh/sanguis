#ifndef SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED

#include "wave.hpp"
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
		time_type delay,
		time_type spawn_interval,
		unsigned waves,
		unsigned spawns_per_wave,
		enemy_type::type);
	
	~infinite();
private:
	void process(
		time_type diff,
		environment const &);
	
	bool ended() const;

	time_type const
		delay_,
		spawn_interval_;
	unsigned const
		waves_,
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
