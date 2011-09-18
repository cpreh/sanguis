#ifndef SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED

#include <sanguis/server/waves/wave_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class wave
{
	FCPPT_NONCOPYABLE(
		wave
	);
protected:
	wave();
public:
	virtual void
	process(
		environment::object &,
		environment::load_context &
	) = 0;

	virtual bool
	ended() const = 0;

	virtual ~wave();
};

}
}
}

#endif
