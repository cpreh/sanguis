#ifndef SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/optional_pos_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_target_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_trail.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_ai_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class context
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	explicit
	context(
		sanguis::server::entities::with_ai_ref
	);

	~context();

	[[nodiscard]]
	bool
	path_find(
		sanguis::creator::pos const &
	);

	void
	clear_path();

	[[nodiscard]]
	sanguis::creator::optional_pos
	destination() const;

	[[nodiscard]]
	sanguis::server::ai::pathing::optional_target
	continue_path();

	[[nodiscard]]
	sanguis::creator::grid const &
	grid() const;

	[[nodiscard]]
	sanguis::server::entities::with_ai &
	me();

	[[nodiscard]]
	sanguis::server::entities::with_ai const &
	me() const;
private:
	sanguis::server::entities::with_ai_ref const me_;

	sanguis::server::ai::pathing::optional_trail trail_;
};

}
}
}

#endif
