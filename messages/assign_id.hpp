#ifndef SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED

#include "../entity_id.hpp"
#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class assign_id : public base {
public:
	assign_id();
	explicit assign_id(
		entity_id player_id_);
	
	entity_id player_id() const;
private:
	entity_id player_id_;
	
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
