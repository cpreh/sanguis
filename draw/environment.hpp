#ifndef SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED

#include "insert_callback.hpp"

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{

class environment {
public:
	environment(
		insert_callback const &,
		load::context const &);
	
	insert_callback const &
	insert() const;

	load::context const &
	context() const;
private:
	insert_callback const &insert_;
	load::context const &context_;
};

}
}

#endif
