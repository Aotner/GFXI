#include "xinput_device.h"

using namespace Blade;

XInputDevice::XInputDevice(int device_id, DeviceType devType)
{

	// Set the device id
	SetDeviceID(device_id);

	// Set the device type
	SetDeviceType(devType);

}

XInputDevice::~XInputDevice()
{
}

void XInputDevice::Update(float deltaTime)
{
	// Update the input states
	XINPUT_STATE tmpState;
	ZeroMemory(&tmpState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD result = XInputGetState(GetDeviceID(), &tmpState);

	// Create an input state
	InputState newState(tmpState);

	// Store state (move current newest to previous, store newState as current)
	SetInputState(newState);
}

bool XInputDevice::SetVibration(float leftMotor, float rightMotor)
{
	XINPUT_VIBRATION vibParams;
	ZeroMemory(&vibParams, sizeof(XINPUT_VIBRATION));

	// scale to xinput range [0..1]-->[0..65536]
	vibParams.wLeftMotorSpeed = static_cast<int>(leftMotor * VIBRATION_THRESHOLD);
	vibParams.wRightMotorSpeed = static_cast<int>(leftMotor * VIBRATION_THRESHOLD);

	DWORD result = XInputSetState(GetDeviceID(), &vibParams);

	return (result == ERROR_SUCCESS);
}
