#ifndef SANGUIS_MESSAGES_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPEED_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <sge/math/vector/basic_decl.hpp>
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class speed : public entity_message {
public:
	speed();
	speed(
		entity_id id,
		vector2 const &);
	
	vector2 const &get() const;
private:
	vector2 speed_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
