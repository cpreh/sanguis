#ifndef SANGUIS_SERVER_AI_TREE_PRIORITY_SEQUENCE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_PRIORITY_SEQUENCE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/container.hpp>
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

class priority_sequence
:
	public sanguis::server::ai::tree::base
{
	FCPPT_NONCOPYABLE(
		priority_sequence
	);
public:
	explicit
	priority_sequence(
		sanguis::server::ai::tree::container &&
	);

	~priority_sequence()
	override;
private:
	sanguis::server::ai::tree::status
	run(
		sanguis::duration
	)
	override;

	sanguis::server::ai::tree::container children_;
};

}
}
}
}

#endif
