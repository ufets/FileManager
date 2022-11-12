#ifndef LAUNCH_H
#define LAUNCH_H

#include <iostream>
#include "SystemDescriptor.hpp"
#include "Dialog.hpp"
#pragma once

void start();
void work(SystemDescriptor& sys, User& user);
void change_user(SystemDescriptor& sys,User& you);
void MainMenu(SystemDescriptor& sys, User& user);

#endif
