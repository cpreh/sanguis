#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


sanguis::server::ai::behavior::base::base(
	sanguis::server::ai::context_ref const _context
)
:
	context_(
		_context
	)
{
}

sanguis::server::ai::behavior::base::~base()
= default;

sanguis::server::entities::transfer_result
sanguis::server::ai::behavior::base::transfer()
{
	return
		sanguis::server::entities::transfer_result();
}

sanguis::server::ai::context &
sanguis::server::ai::behavior::base::context()
{
	return
		context_.get();
}

sanguis::server::ai::context const &
sanguis::server::ai::behavior::base::context() const
{
	return
		context_.get();
}

sanguis::server::entities::with_ai &
sanguis::server::ai::behavior::base::me()
{
	return
		this->context().me();
}

sanguis::server::entities::with_ai const &
sanguis::server::ai::behavior::base::me() const
{
	return
		this->context().me();
}
