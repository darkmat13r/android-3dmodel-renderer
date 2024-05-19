//
// Created by Dark Matter on 5/13/24.
//
#include "Component.h"
#include "AndroidOut.h"

void Component::update() {
    //DO NOTHING
}

void Component::render(Mat4f *f) {
    //DO NOTHING
}

void Component::onAttach() {
 //DO NOTHING
}

Component::Component() {
    transform = std::make_shared<Transform>();
    onCreate();
}

void Component::onCreate() {
    //DO NOTHING
}

void Component::onDestroy() {
    //DO NOTHING
}

Component::~Component() {
    aout << "Component is destroyed : " << this << std::endl;
}

