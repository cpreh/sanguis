#ifndef SANGUIS_SERVER_AI_TREE_LEAF_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_LEAF_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base_unique_ptr.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

class leaf
:
	public sanguis::server::ai::tree::base
{
	FCPPT_NONMOVABLE(
		leaf
	);
public:
	explicit
	leaf(
		sanguis::server::ai::behavior::base_unique_ptr &&
	);

	~leaf()
	override;
private:
	[[nodiscard]]
	sanguis::server::entities::transfer_result
	transfer()
	override;

	[[nodiscard]]
	sanguis::server::ai::status
	run(
		sanguis::duration
	)
	override;

	sanguis::server::ai::behavior::base_unique_ptr const behavior_;

	bool started_;
};

}
}
}
}

#endif
