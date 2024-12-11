Adaptive Compression Bandage for Musculoskeletal Injury

This project introduces an Adaptive Compression Bandage System that dynamically adjusts compression pressure using real-time data from SpO2 and heart rate sensors. It improves therapy for musculoskeletal injuries like sprains, ensuring effective treatment and enhanced patient comfort.

Features

- Dynamic Adjustment: Automatically regulates compression based on sensor feedback.
- Non-Invasive Monitoring: Tracks blood oxygen saturation (SpO2) and heart rate using PPG.
- Arduino-Based Control: Utilizes air pumps for precise inflation/deflation.

Hardware

- MAX30100 SpO2 Sensor
- Heart Rate Sensor
- Force Sensing Resistor (FSR)
- Arduino UNO
- 12V Air Pumps
- 9V Battery

How It Works

- SpO2 > 90% & Heart Rate > 60 bpm: Bandage inflates for optimal compression.
- SpO2 < 90% or Heart Rate < 60 bpm: Bandage deflates to reduce compression.

