#ifndef SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../enemy_type.hpp"
#include "../../time_delta_fwd.hpp"
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
	explicit single(
		enemy_type::type
	);

	~single();
private:
	void
	process(
		sanguis::time_delta const &,
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	enemy_type::type const etype_;

	bool spawned_;
};

}
}
}

#endif
