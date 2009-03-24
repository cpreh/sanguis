#ifndef SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED

#include "../load/context_fwd.hpp"
#include "insert_callback.hpp"
#include "system_fwd.hpp"

namespace sanguis
{
namespace draw
{

class environment {
public:
	environment(
		insert_callback const &,
		load::context const &,
		draw::system &);
	
	insert_callback const &
	insert() const;

	load::context const &
	context() const;

	draw::system &
	system() const;
private:
	insert_callback const insert_;
	load::context const   &context_;
	draw::system          &system_;
};

}
}

#endif
