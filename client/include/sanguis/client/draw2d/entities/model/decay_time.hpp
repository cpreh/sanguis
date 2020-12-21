#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class decay_time
{
	FCPPT_NONCOPYABLE(
		decay_time
	);
public:
	decay_time(
		sanguis::diff_clock_cref,
		sanguis::duration const &
	);

	decay_time(
		decay_time &&
	)
	noexcept;

	decay_time &
	operator=(
		decay_time &&
	)
	noexcept;

	~decay_time();

	[[nodiscard]]
	bool
	ended() const;
private:
	sanguis::diff_timer timer_;
};

}
}
}
}
}

#endif
