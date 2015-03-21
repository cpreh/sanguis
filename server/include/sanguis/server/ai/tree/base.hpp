#ifndef SANGUIS_SERVER_AI_TREE_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/tree/base_fwd.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace tree
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	sanguis::server::entities::transfer_result
	transfer() = 0;

	virtual
	sanguis::server::ai::status
	run(
		sanguis::duration
	) = 0;
};

}
}
}
}

#endif
