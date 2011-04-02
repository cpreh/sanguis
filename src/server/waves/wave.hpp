#ifndef SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED

#include "wave_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../../time_type.hpp"
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
	virtual void process(
		sanguis::time_type diff,
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
