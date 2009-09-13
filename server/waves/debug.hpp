#ifndef SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED

#include "wave.hpp"

namespace sanguis
{
namespace server
{
namespace waves
{

class debug : public wave {
public:
	debug();
private:
	void
	process(
		time_type diff,
		environment::object_ptr
	);

	bool ended() const;

	bool spawned;
};

}
}
}

#endif
