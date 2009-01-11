#ifndef SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_STATUS_HPP_INCLUDED

#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

struct status {
	status(
		perk_type::type);
	
	bool chosen() const;
	void choose();

	perk_type::type type() const;
private:
	perk_type::type type_;
	bool chosen_;
};

}
}
}

#endif
