#pragma once

#include <iostream>
#include <vector>

#include "Environment.h"
#include "Robot.h"
#include "Etat.h"

std::ostream& operator<<(std::ostream& s, Etat& e);
std::ostream& operator<<(std::ostream& s, Environment& map);