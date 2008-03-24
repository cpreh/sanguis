#ifndef SANGUIS_MESSAGES_SEND_UNIQUE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_SEND_UNIQUE_ID_HPP_INCLUDED

#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class send_unique_id : public entity_message {
public:
	send_unique_id();
	explicit send_unique_id(entity_id);
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
