#include "oled.h"
#include "i2c_manager.h"
#include "EEG.h"

int main() {
	EEGSerial eeg;
	eeg.startListening();  // Start the data reception thread

	if (I2C_Open() < 0) {
		printf("Failed to open I2C.\n");
		return -1;
	}
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0, 0, "Attention: ");
	OLED_ShowString(0, 2, "Meditation: ");
	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//Use getDataMutex() to access the mutex
		{
			std::lock_guard<std::mutex> lock(eeg.getDataMutex());
			OLED_ShowUInt8(88, 0, EEGSerial::attention);
			OLED_ShowUInt8(96, 2, EEGSerial::meditation);
		}
	}
	return 0;
}