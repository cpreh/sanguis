#ifndef SANGUIS_SERVER_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_HPP_INCLUDED

#include "../messages/types.hpp"
#include "../entity_id.hpp"
#include "../entity_type.hpp"
#include <memory>

namespace sanguis
{
namespace server
{
class entity
{
	public:
	typedef messages::space_unit time_type;

	entity(const entity_id id_);
	entity_id id() const;

	// pure virtuals
	virtual messages::pos_type center() const = 0;
	virtual messages::pos_type speed() const = 0;
	virtual messages::space_unit angle() const = 0;
	virtual messages::space_unit health() const = 0;
	virtual messages::space_unit max_health() const = 0;
	virtual entity_type::type type() const = 0;
	virtual void update(const time_type) = 0;
	virtual ~entity();
	private:
	entity_id id_;
};

typedef std::auto_ptr<entity> entity_ptr;
}
}

#endif
