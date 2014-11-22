#ifndef SANGUIS_SERVER_AI_BEHAVIOR_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/behavior/base_fwd.hpp>
#include <sanguis/server/ai/behavior/status_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	explicit
	base(
		sanguis::server::ai::context &
	);
public:
	virtual
	~base() = 0;

	bool
	is_started() const;

	bool
	start();

	virtual
	bool
	do_start() = 0;

	void
	stop();

	virtual
	void
	do_stop() = 0;

	virtual
	sanguis::server::ai::behavior::status
	update(
		sanguis::duration
	) = 0;
protected:
	sanguis::server::ai::context &
	context();

	sanguis::server::ai::context const &
	context() const;

	sanguis::server::entities::with_ai &
	me();

	sanguis::server::entities::with_ai const &
	me() const;
private:
	sanguis::server::ai::context &context_;

	bool started_;
};

}
}
}
}

#endif
