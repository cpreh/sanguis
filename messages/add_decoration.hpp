#ifndef SANGUIS_MESSAGES_ADD_DECORATION_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_DECORATION_HPP_INCLUDED

#include "add.hpp"
#include "types.hpp"
#include "../decoration_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class add_decoration : public add {
public:
	add_decoration();
	add_decoration(
		entity_id id,
		decoration_type::type,
		pos_type const &,
		space_unit angle,
		space_unit health,
		space_unit max_health,
		dim_type const &);
	
	decoration_type::type ptype() const;
private:
	decoration_type::type ptype_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
