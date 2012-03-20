#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/entity_map.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_real_decl.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class simple
:
	public ai::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		entities::with_ai &me,
		entities::auto_weak_link owner
	);

	~simple();
private:
	void
	update();

	void
	target_enters(
		entities::with_body &
	);

	void
	target_leaves(
		entities::with_body &
	);

	sanguis::diff_timer pos_timer_;

	entities::with_ai &me_;

	entities::auto_weak_link
		target_,
		owner_;

	entity_map potential_targets_;

	typedef fcppt::random::distribution::uniform_real<
		server::space_unit
	> distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		distribution
	> random_variate;

	random_variate
		timer_rng_,
		fuzzy_target_rng_;
};

}
}
}

#endif
