#ifndef SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../enemy_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class single
:
	public wave
{
	FCPPT_NONCOPYABLE(
		single
	);
public:
	single(
		sanguis::diff_clock const &,
		enemy_type::type
	);

	~single();
private:
	void
	process(
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	sanguis::diff_clock const &diff_clock_;

	enemy_type::type const etype_;

	bool spawned_;
};

}
}
}

#endif
