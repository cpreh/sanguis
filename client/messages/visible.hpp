#ifndef SANGUIS_CLIENT_MESSAGES_VISIBLE_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_VISIBLE_HPP_INCLUDED

#include "../entity_id.hpp"

namespace sanguis
{
namespace client_messages
{

class visible {
public:
	visible(
		entity_id,
		bool visible_);

	entity_id id() const;

	bool get() const;
private:
	entity_id const id_;
	bool const visible_;
};

}
}

#endif
