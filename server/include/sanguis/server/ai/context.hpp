#ifndef SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_target_fwd.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::server::entities::with_ai &
	);

	~context();

	bool
	path_find(
		sanguis::creator::pos
	);

	void
	clear_path();

	sanguis::server::ai::pathing::optional_target const
	continue_path();

	sanguis::creator::grid const &
	grid() const;

	sanguis::server::entities::with_ai &
	me();
private:
	sanguis::server::entities::with_ai &me_;

	sanguis::server::ai::pathing::trail trail_;
};

}
}
}

#endif
