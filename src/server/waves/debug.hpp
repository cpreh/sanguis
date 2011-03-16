#ifndef SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED

#include "wave.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class debug
:
	public wave
{
	FCPPT_NONCOPYABLE(
		debug
	);
public:
	debug();

	~debug();
private:
	void
	process(
		time_type diff,
		environment::object_ptr,
		environment::load_context_ptr
	);

	bool
	ended() const;

	bool spawned_;
};

}
}
}

#endif
