#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include "with_ai_fwd.hpp"
#include "with_auras.hpp"
#include "with_weapon.hpp"
#include "../ai/scoped_ptr.hpp"
#include "../ai/create_function.hpp"
#include "../weapons/unique_ptr.hpp"
#include "../../diff_clock_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public entities::with_auras,
	public entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		with_ai
	);
protected:
	with_ai(
		sanguis::diff_clock const &,
		ai::create_function const &,
		weapons::unique_ptr start_weapon
	);

	~with_ai();

	virtual void
	on_update();
private:
	void
	on_create();

	ai::create_function const create_ai_;

	ai::scoped_ptr ai_;
};

}
}
}

#endif
