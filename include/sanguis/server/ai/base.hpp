#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
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
	void
	in_range(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	distance_changes(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	out_of_range(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	update() = 0;
};

}
}
}

#endif
