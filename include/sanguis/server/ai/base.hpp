#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
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
	sanguis::server::entities::auto_weak_link
	target() const = 0;

	// This could dynamically change in the future!
	virtual
	sanguis::server::ai::sight_range const
	sight_range() const = 0;

	virtual
	sanguis::server::ai::update_result
	in_range(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::server::ai::update_result
	distance_changes(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::server::ai::update_result
	out_of_range(
		sanguis::server::entities::with_body &
	);
};

}
}
}

#endif
