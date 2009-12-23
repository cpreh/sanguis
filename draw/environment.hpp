#ifndef SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_DRAW_ENVIRONMENT_HPP_INCLUDED

#include "../load/context_fwd.hpp"
#include "sprite/colored/system.hpp"
#include "sprite/normal/system.hpp"
#include "sprite/client/system.hpp"
#include "sprite/particle/system.hpp"
#include "insert_callback.hpp"
#include <fcppt/function/object.hpp>

namespace sanguis
{
namespace draw
{

class environment {
public:
	environment(
		insert_callback const &,
		load::context const &,
		sprite::colored::system &,
		sprite::normal::system &,
		sprite::client::system &,
		sprite::particle::system &
	);
	
	insert_callback const &
	insert() const;

	load::context const &
	context() const;

	sprite::colored::system &
	colored_system() const;

	sprite::normal::system &
	normal_system() const;

	sprite::client::system &
	client_system() const;

	sprite::particle::system &
	particle_system() const;
private:
	insert_callback const insert_;
	load::context const   &context_;
	sprite::colored::system &colored_system_;
	sprite::normal::system &normal_system_;
	sprite::client::system &client_system_;
	sprite::particle::system &particle_system_;
};

}
}

#endif
