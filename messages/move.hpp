#ifndef SANGUIS_MESSAGES_MOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MOVE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class move : public entity_message {
public:
	move();
	move(
		entity_id id,
	    	pos_type const &pos);
	
	pos_type const &pos() const;
private:
	pos_type pos_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
