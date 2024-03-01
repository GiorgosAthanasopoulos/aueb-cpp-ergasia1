#pragma once

#include <string>
#include <list>
#include <memory>

#include "Button.h"

std::list<std::string> splitDescription(std::string description);
std::list<std::string> splitActors(std::string actors);
void open(std::string cmd);
std::shared_ptr<Button> getButtonFromList(std::list<std::shared_ptr<Button>> list, int index);
void toLowerCase(std::string* input);
