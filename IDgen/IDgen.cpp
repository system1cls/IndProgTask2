#include "IDgen.hpp"

IDgen::IDgen() {

}

void IDgen::set_seed(ulong seed) {
	this->generator.seed(seed);
}

ulong IDgen::gen() {
	return generator();
}
