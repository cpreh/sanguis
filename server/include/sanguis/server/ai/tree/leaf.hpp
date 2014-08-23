#ifndef SANGUIS_SERVER_AI_TREE_LEAF_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_LEAF_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/behavior/base_unique_ptr.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/status_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
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
	sanguis::server::ai::tree::status
	run(
		sanguis::duration
	)
	override;

	void
	clear()
	override;

	sanguis::server::ai::behavior::base_unique_ptr const behavior_;
};

}
}
}
}

#endif
