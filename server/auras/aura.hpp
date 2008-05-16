#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "../../messages/types.hpp"
#include "../../time_type.hpp"
#include "../entities/entity_fwd.hpp"
#include "../teams.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class aura {
public:
	virtual ~aura();

	struct influence {
		enum type {
			buff,
			debuff
		};
	};

	void pos(
		messages::pos_type const&);
protected:
	aura(
		messages::circle_type const&,
		team::type team,
		influence::type);
private:
	void update(
		time_type,
		entities::container &entities);

	bool invulnerable() const;
	messages::space_unit max_speed() const;
	messages::dim_type dim() const;

	virtual void do_effect(
		entities::entity &target) = 0;

	messages::circle_type circle_;
	team::type            team_;
	influence::type       influence_;
};

}
}
}

#endif
