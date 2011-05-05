#ifndef SANGUIS_SERVER_AI_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_AI_DEBUG_HPP_INCLUDED

#include "base.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../entities/with_ai_fwd.hpp"
#include "../../time_delta_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

class debug
:
	public ai::base 
{
	FCPPT_NONCOPYABLE(
		debug
	);
public:
	debug(
		entities::with_ai &me,
		entities::auto_weak_link owner
	);

	~debug();
private:
	void
	update(
		sanguis::time_delta const &
	);

	entities::with_ai &me_;
};

}
}
}

#endif
