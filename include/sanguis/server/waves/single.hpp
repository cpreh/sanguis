#ifndef SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SINGLE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace waves
{

class single
:
	public sanguis::server::waves::wave
{
	FCPPT_NONCOPYABLE(
		single
	);
public:
	single(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::creator::enemy_type
	);

	~single();
private:
	void
	process(
		sanguis::server::environment::object &,
		sanguis::server::environment::load_context &
	);

	bool
	ended() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::creator::enemy_type const etype_;

	bool spawned_;
};

}
}
}

#endif
