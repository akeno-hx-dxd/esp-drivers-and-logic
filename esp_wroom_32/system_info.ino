#include <WiFi.h>
#include <esp_system.h>
#include <esp_chip_info.h>

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n\n================================");
  Serial.println("       ESP32 SYSTEM INFO");
  Serial.println("================================");
  
  // Basic chip information
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  
  Serial.printf("Chip Model: %s\n", ESP.getChipModel());
  Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
  Serial.printf("Number of cores: %d\n", chip_info.cores);
  Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
  
  // Flash information
  Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("Flash Speed: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);
  Serial.printf("Flash Mode: %s\n", (ESP.getFlashChipMode() == FM_QIO) ? "QIO" : 
                                     (ESP.getFlashChipMode() == FM_QOUT) ? "QOUT" :
                                     (ESP.getFlashChipMode() == FM_DIO) ? "DIO" :
                                     (ESP.getFlashChipMode() == FM_DOUT) ? "DOUT" : "UNKNOWN");
  
  // Memory information
  Serial.printf("Total heap: %d bytes\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Total PSRAM: %d bytes\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
  
  // MAC addresses
  Serial.printf("WiFi MAC: %s\n", WiFi.macAddress().c_str());
  
  // Features
  Serial.println("\nFeatures:");
  Serial.printf("  WiFi: %s\n", (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "YES" : "NO");
  Serial.printf("  Bluetooth: %s\n", (chip_info.features & CHIP_FEATURE_BT) ? "YES" : "NO");
  Serial.printf("  Bluetooth LE: %s\n", (chip_info.features & CHIP_FEATURE_BLE) ? "YES" : "NO");
  
  // SDK and Arduino info
  Serial.printf("ESP-IDF Version: %s\n", ESP.getSdkVersion());
  Serial.printf("Arduino ESP32 Version: %s\n", ESP_ARDUINO_VERSION_STR);
  
  // Reset information
  Serial.printf("Reset Reason: %s\n", getResetReason(esp_reset_reason()));
  
  // Temperature (if available)
  Serial.printf("Internal Temperature: %.1f°C\n", temperatureRead());
  
  Serial.println("\n================================");
  Serial.println("         SYSTEM READY");
  Serial.println("================================\n");
}

void loop() {
  // Print some runtime stats every 10 seconds
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 10000) {
    lastPrint = millis();
    
    Serial.println("--- Runtime Stats ---");
    Serial.printf("Uptime: %lu seconds\n", millis() / 1000);
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Min Free Heap: %d bytes\n", ESP.getMinFreeHeap());
    Serial.printf("Max Alloc Heap: %d bytes\n", ESP.getMaxAllocHeap());
    Serial.println();
  }
  
  delay(1000);
}

// Helper function to get reset reason
const char* getResetReason(esp_reset_reason_t reason) {
  switch (reason) {
    case ESP_RST_UNKNOWN: return "UNKNOWN";
    case ESP_RST_POWERON: return "POWERON_RESET";
    case ESP_RST_EXT: return "EXTERNAL_RESET";
    case ESP_RST_SW: return "SOFTWARE_RESET";
    case ESP_RST_PANIC: return "PANIC_RESET";
    case ESP_RST_INT_WDT: return "INTERRUPT_WDT";
    case ESP_RST_TASK_WDT: return "TASK_WDT";
    case ESP_RST_WDT: return "WDT_RESET";
    case ESP_RST_DEEPSLEEP: return "DEEPSLEEP_RESET";
    case ESP_RST_BROWNOUT: return "BROWNOUT_RESET";
    case ESP_RST_SDIO: return "SDIO_RESET";
    default: return "UNKNOWN";
  }
}
