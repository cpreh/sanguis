#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class simple
:
	public sanguis::server::ai::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	explicit
	simple(
		sanguis::server::entities::with_ai &
	);

	~simple();
private:
	void
	in_range(
		sanguis::server::entities::with_body &
	)
	override;

	void
	distance_changes(
		sanguis::server::entities::with_body &
	)
	override;

	void
	out_of_range(
		sanguis::server::entities::with_body &
	)
	override;

	void
	update()
	override;

	sanguis::server::entities::with_ai &me_;

	sanguis::server::entities::auto_weak_link target_;
};

}
}
}

#endif
