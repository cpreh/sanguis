#ifndef SANGUIS_SERVER_AI_DEBUG_HPP_INCLUDED
#define SANGUIS_SERVER_AI_DEBUG_HPP_INCLUDED

#include "base.hpp"
#include "../entities/with_ai_fwd.hpp"
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
	explicit debug(
		entities::with_ai &me
	);

	~debug();
private:
	void
	update();

	entities::with_ai &me_;
};

}
}
}

#endif
