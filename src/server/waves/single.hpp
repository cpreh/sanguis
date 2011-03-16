#ifndef SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED

#include "wave.hpp"
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
	explicit single(
		enemy_type::type
	);

	~single();
private:
	void
	process(
		time_type diff,
		environment::object_ptr,
		environment::load_context_ptr
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
