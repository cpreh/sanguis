#ifndef SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED

#include <sanguis/server/waves/wave.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
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
		sanguis::random_generator &,
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

	sanguis::random_generator &random_generator_;

	enemy_type::type const etype_;

	bool spawned_;
};

}
}
}

#endif
