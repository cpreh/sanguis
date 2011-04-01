#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include "with_ai_fwd.hpp"
#include "with_auras.hpp"
#include "with_weapon.hpp"
#include "../ai/unique_ptr.hpp"
#include "../ai/create_function.hpp"
#include "../weapons/unique_ptr.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public with_auras,
	public with_weapon
{
	FCPPT_NONCOPYABLE(
		with_ai
	);
protected:
	explicit with_ai(
		ai::create_function const &,
		weapons::unique_ptr start_weapon
	);

	~with_ai();

	virtual void
	on_update(
		time_type
	);
private:
	void
	on_transfer(
		collision::create_parameters const &
	);

	ai::create_function const create_ai_;

	ai::unique_ptr ai_;
};

}
}
}

#endif
