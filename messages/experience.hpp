#ifndef SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class experience : public entity_message {
public:
	experience();
	experience(
		entity_id id,
		exp_type exp);
	exp_type exp() const;
private:
	exp_type exp_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
