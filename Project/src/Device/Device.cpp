/*
using namespace GFW;

Device::Device() {
}
Device::~Device() {
}


void Device::Begin(String str) {
	assert(this->device.find(str) == this->device.end());
	this->stack.push_back(&this->device[str]);
}

void Device::End() {
	assert(this->stack_count,TEXT("Error:DeviceStackCount"));
	this->stack.pop_back();
	if(this->stack.size()){}
}
*/