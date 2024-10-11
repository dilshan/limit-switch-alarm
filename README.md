## Alarm unit for limit switches or flow switches

![Alarm controller in action](https://raw.githubusercontent.com/dilshan/limit-switch-alarm/refs/heads/main/resources/limit-switch-alarm-ucase.jpeg)

This project introduces a cost-effective and do-it-yourself (DIY) solution for monitoring floater switches and activating alarms in various applications. The designed circuit, which is based on the PIC12F508 microcontroller, effectively detects changes in floater switch status and triggers the alarm. The system is designed to operate with a 12V DC power supply and utilizes a 230V AC buzzer unit for audible alerts.

The circuit includes a mute function that temporarily silences the alarm for a specified duration. Additionally, a built-in timeout mechanism ensures continuous alarm activation if the floater switch remains closed for an extended period, indicating a potential emergency. The project's modular design and clear documentation facilitate easy assembly and customization, making it suitable for a wide range of applications, including home automation, industrial monitoring, and environmental sensing.

![Prototype version of alarm controller](https://raw.githubusercontent.com/dilshan/limit-switch-alarm/refs/heads/main/resources/limit-switch-alarm-prototype.jpg)

### Bill of materials

| Reference  | Value            | Qty | Datasheet                                                        |
|------------|------------------|-----|------------------------------------------------------------------|
| C101       | [100MFD / 16V](https://s.click.aliexpress.com/e/_EJ7MXe9)     | 1   |                                                                  |
| C102       | [0.1MFD / 50V](https://s.click.aliexpress.com/e/_oCeppvT)     | 1   |                                                                  |
| D101       | [1N4007](https://s.click.aliexpress.com/e/_ExTh0Mz)           | 1   | http://www.vishay.com/docs/88503/1n4001.pdf                      |
| K101       | [JQC-3F-12VDC-1ZS](https://s.click.aliexpress.com/e/_EyyWHrr) | 1   | https://www.futurlec.com/Datasheet/Relays/JQC-3FF.pdf            |
| Q101       | [2SD400](https://s.click.aliexpress.com/e/_mNK5TeM)           | 1   | https://datasheet.octopart.com/2SD400-Sanyo-datasheet-101823.pdf |
| R101       | [10K](https://s.click.aliexpress.com/e/_EJJGJg1)              | 1   |                                                                  |
| R102       | [5.6K](https://s.click.aliexpress.com/e/_EJJGJg1)             | 1   |                                                                  |
| R103, R104 | [22K](https://s.click.aliexpress.com/e/_EJJGJg1)              | 2   |                                                                  |
| U101       | [PIC12F508-I/P](https://s.click.aliexpress.com/e/_EvdDNTr)    | 1   | https://ww1.microchip.com/downloads/en/DeviceDoc/41236E.pdf      |
| U102       | [L7805](https://s.click.aliexpress.com/e/_opm5dbr)            | 1   | https://www.st.com/resource/en/datasheet/l78.pdf                 |

### PIC12F508 firmware

The firmware for this project is developed using the [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide) and the [XC8 C compiler](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers). The latest firmware is available in the [/firmware](https://github.com/dilshan/limit-switch-alarm/tree/main/firmware) directory in this repository. 

### External Components

This project requires several external components:

- [12V 1A Power Supply Unit (PSU)](https://s.click.aliexpress.com/e/_mqQEkSY): Provides the necessary power for the microcontroller, relay, and other electronic components.
- [Pump Float Switch](https://s.click.aliexpress.com/e/_EuamfjX): A float switch is used to detect changes in liquid levels. Select a float switch that is compatible with the intended application and capable of reliably triggering the alarm system.
- [AC High dB Mechanical Buzzer](https://s.click.aliexpress.com/e/_oBIDYBj) or [Industrial Alarm](https://s.click.aliexpress.com/e/_oDt7jiN): A loud and attention-grabbing alarm is essential for alerting users to potential emergencies. Consider using an AC-powered mechanical buzzer or industrial alarm that is suitable for the desired noise level.
- [Push Switch](https://s.click.aliexpress.com/e/_EvkMX2H): A momentary push switch is used to manually mute the alarm.
