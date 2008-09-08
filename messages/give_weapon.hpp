#ifndef SANGUIS_MESSAGES_GIVE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_GIVE_WEAPON_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class give_weapon : public entity_message {
public:
	give_weapon();
	give_weapon(
		entity_id id,
		enum_type weapon,
		size_type magazine_size);
	enum_type weapon() const;
	size_type magazine_size() const;
private:
	enum_type weapon_;
	size_type magazine_size_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
