#ifndef SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED

#include "entity_message.hpp"
#include "perk_list.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class available_perks : public entity_message {
public:
	available_perks();
	explicit available_perks(
		perk_list const &);
	
	perk_list const &
	perks() const;
private:
	perk_list perks_;
	
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};
	
}
}

#endif
