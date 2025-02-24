#include "oled.h"
#include "i2c_manager.h"
#include "EEG.h"
#include "rec_uart.h"

int main() {
	EEGSerial eeg;
	RecUart recUart;

	uint8_t attention, meditation;
	uint8_t bpm;
	float spo2;

	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0, 0, "Attention: ");
	OLED_ShowString(0, 2, "Meditation: ");
	OLED_ShowString(0, 4, "bpm: ");
	OLED_ShowString(0, 6, "spo2: ");

	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		eeg.getData(attention, meditation);
		OLED_ShowUInt8_twochar(88, 0, attention);
		OLED_ShowUInt8_twochar(96, 2, meditation);

		recUart.getData(bpm, spo2);
		OLED_ShowUInt8_threechar(40, 4, bpm);
		OLED_ShowFloat(48, 6, spo2);
		std::cout << "Attention: " << (int)attention << ", Meditation: " << (int)meditation << std::endl;
		std::cout << "Heart Rate: " << (int)bpm << " BPM, SpO2: " << spo2 << "%" << std::endl << std::endl;
	}
	return 0;
}