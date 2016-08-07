// Cargo: what the vessel is carrying
#include "cargo.h"
#include "vessel.h"

// Define the vessel structure here
struct vessel create_vessel(const char *name, double length, double depth,
			    struct cargo crg);

void print_vessel(const struct vessel *ship);
