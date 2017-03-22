#pragma once
#include "Controller.h"

typedef struct {
	Controller* controller;
} UI;

UI* createUI(Controller* c);
void destroyUI(UI* ui);

void startUI(UI* ui);
