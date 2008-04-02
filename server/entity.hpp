#ifndef SANGUIS_SERVER_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_HPP_INCLUDED

#include "../messages/types.hpp"
#include "../entity_id.hpp"

namespace sanguis
{
namespace server
{
class entity
{
	public:
	typedef messages::space_unit time_type;

	// haha, no cpp file for this small functions!
	entity(const entity_id id_) : id_(id_) {}
	entity_id id() const { return id_; }

	// pure virtuals
	virtual messages::pos_type center() const = 0;
	virtual messages::pos_type speed() const = 0;
	virtual messages::space_unit angle() const = 0;
	virtual messages::space_unit health() const = 0;
	virtual void update(const time_type) = 0;
	private:
	entity_id id_;
};
}
}

#endif
