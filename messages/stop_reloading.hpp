#ifndef SANGUIS_MESSAGES_STOP_RELOADING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STOP_RELOADING_HPP_INCLUDED

#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class stop_reloading : public entity_message {
public:
	stop_reloading();
	explicit stop_reloading(
		entity_id id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
