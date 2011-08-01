#ifndef SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_DEBUG_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../diff_clock_fwd.hpp"
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
	explicit debug(
		sanguis::diff_clock const &
	);

	~debug();
private:
	void
	process(
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	sanguis::diff_clock const &diff_clock_;

	bool spawned_;
};

}
}
}

#endif
