#pragma once

#include <string>
#include <vector>
#include <list>

#include "interface.hpp"
#include "alertable.hpp"

const std::string ALL_GOOD = "All good.";

class Alert
{
    // DECLARE_CLASS_AS_INTERFACE(Alert) // It's not exactly an interface but an
    //   abstract class which is pretty much the same thing in c++ anyway.

private:
    std::string name;
    bool active;
    std::string message;
    std::vector<Alertable *> alertables;

public:
    Alert(std::string name);
    Alert(std::string name, Alertable *alertable);
    // Alert(std::string name, std::list<Alertable *> alertables);
    Alert(Alert *alert);

    auto addAlertable(Alertable *alertable) -> Alertable *;
    auto removeAlertable(Alertable *alertable) -> Alertable *;

    auto activate(std::string message) -> void;
    auto clear() -> void;
    auto isActive() -> bool;
    auto getName() -> std::string;
    auto getMessage() -> std::string;
    auto toString() -> std::string;
};
