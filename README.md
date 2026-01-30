# STM32 Buzzer Control via CLI

An STM32 project that controls a piezo buzzer through a Command Line Interface (CLI). The project demonstrates the integration of PWM-based tone generation with an interactive command line over UART.

## Overview

This project combines several important embedded technologies:
- **Command Line Interface (CLI)**: Based on the EmbeddedCli Library
- **PWM-based Tone Generation**: Precise control of a buzzer via Timer-PWM
- **UART Communication**: Bidirectional serial interface
- **Melody Playback**: Pre-configured melodies (Super Mario, Imperial March)

## Hardware Requirements

- **STM32 Nucleo-U545RE** Development Board
- **Buzzer Click Board**: PAM8904-based buzzer (e.g., MikroElektronika BUZZ 3 Click)
  - [Product Page](https://www.mikroe.com/buzz-3-click)
  - [Schematic](https://download.mikroe.com/documents/add-on-boards/click/buzz_3_click/buzz-3-click-schematic-v100.pdf)
  - [PAM8904 Datasheet](https://download.mikroe.com/documents/datasheets/PAM8904_datasheet.pdf)
- USB cable for programming and serial communication
- Onboard LED (LD2) for additional visualization

## Main Features

### CLI Commands

1. **`set_led_state <on|off>`**
   - Turns the onboard LED on or off
   - Example: `set_led_state on`

2. **`buzzer_play_sound <frequency_Hz> <duration_ms>`**
   - Plays a tone with specified frequency and duration
   - Frequency range: 100 - 2000 Hz
   - Duration range: 1 - 10000 ms
   - Example: `buzzer_play_sound 440 1000` (440Hz A-note for 1 second)

3. **`play_mario_theme`**
   - Plays the Super Mario Theme melody
   - Fully pre-configured note sequence

4. **`play_imperial_march`**
   - Plays the Imperial March Theme (Star Wars)
   - Epic melody for true nerds 🎵

5. **Standard CLI Commands**
   - `help` - Shows all available commands
   - `clear` - Clears the terminal screen

## Technical Details

### PWM Configuration
- **Timer**: TIM1, Channel 3
- **Prescaler**: 3
- **System Clock**: 4 MHz (important for correct frequency calculation!)
- **Duty Cycle**: 50% for optimal volume
- **Frequency Range**: 100 Hz - 2000 Hz

### PAM8904 Buzzer Driver
The buzzer uses the PAM8904 audio amplifier:
- **EN1**: GPIO_PIN_RESET (Ground)
- **EN2**: GPIO_PIN_SET (Shutdown-Control)
- Configuration for single-ended operation (see Datasheet p. 5)

### Melody Implementation
Melodies are defined as arrays of frequency-duration pairs:
```c
static const struct {
    unsigned int frequency;  // Frequency in Hz
    unsigned int duration;   // Duration in ms
} super_mario_theme[] = {
    {659, 150},  // E5
    {659, 150},  // E5
    {0, 150},    // REST (pause)
    // ... more notes
};
```

## Project Structure

```
├── Core/                        # STM32 HAL and system files
│   ├── Inc/                     # Header files (gpio.h, tim.h, usart.h)
│   └── Src/                     # Peripheral configuration
├── User_App/                    # Application-specific modules
│   ├── BlinkyLed/               # LED control
│   ├── Buzzer/                  # Buzzer control (PWM, tone generation)
│   ├── CliBinding/              # CLI command bindings
│   │   ├── CliBinding.c         # Command implementations
│   │   ├── SuperMarioTheme.h    # Super Mario melody
│   │   └── ImperialMarchTheme.h # Imperial March melody
│   ├── Console/                 # UART console interface
│   └── UserMain/                # Main application logic
└── Utils/                       # Utility libraries
    ├── EmbeddedCli/             # CLI library (submodule)
    └── EmbeddedUtils/           # Common utilities (submodule)
```

## Installation and Usage

### Building the Project

1. **Clone the repository (with submodules!):**
   ```bash
   git clone <repository-url> --recursive
   cd 21_BuzzOnCliCmd
   ```
   
   ⚠️ **Important**: The `--recursive` flag is essential to load the EmbeddedCli and EmbeddedUtils submodules!

2. **If you forgot submodules:**
   ```bash
   git submodule update --init --recursive
   ```

3. **Build with STM32CubeIDE:**
   - Import project into STM32CubeIDE
   - Build the project (Ctrl+B)
   - Flash to the Nucleo board

### Connecting to the CLI

1. **Connect the Nucleo board via USB**

2. **Find the virtual COM port:**
   ```bash
   ls /dev/ttyACM*
   # Usually: /dev/ttyACM0
   ```

3. **Connect using screen:**
   ```bash
   screen /dev/ttyACM0 115200
   ```

4. **Alternative terminal programs:**
   ```bash
   # minicom
   minicom -D /dev/ttyACM0 -b 115200
   
   # PuTTY (GUI)
   putty -serial /dev/ttyACM0 -serspeed 115200
   ```

### Using the CLI

After connecting, you'll see the CLI prompt. Try these commands:

```bash
# Show help
> help

# Turn on LED
> set_led_state on

# Play a simple tone (440 Hz A-note for 1 second)
> buzzer_play_sound 440 1000

# Play Super Mario Theme
> play_mario_theme

# Play Imperial March
> play_imperial_march

# Turn off LED
> set_led_state off
```

## Example Sessions

### Playing a Scale
```bash
> buzzer_play_sound 262 500  # C4
> buzzer_play_sound 294 500  # D4
> buzzer_play_sound 330 500  # E4
> buzzer_play_sound 349 500  # F4
> buzzer_play_sound 392 500  # G4
> buzzer_play_sound 440 500  # A4
> buzzer_play_sound 494 500  # B4
> buzzer_play_sound 523 500  # C5
```

### Simulating an Alarm
```bash
> buzzer_play_sound 1000 200
> buzzer_play_sound 1500 200
> buzzer_play_sound 1000 200
> buzzer_play_sound 1500 200
```

## Error Handling

The project features comprehensive error handling:

### Assertions
- System Clock must be exactly 4 MHz
- Frequency must be in the range 100-2000 Hz
- Duration must be in the range 1-10000 ms
- On assertion failures: Breakpoint output via CLI

### CLI Errors
- Invalid arguments are caught and reported
- Helpful error messages with correct syntax guidance

## Debugging Tips
### No sound audible?
1. Check buzzer connection (EN1, EN2, PWM signal)
2. Verify timer configuration with oscilloscope
3. Ensure System Clock = 4 MHz
4. Test with low frequencies (200-500 Hz)

### CLI not responding?
1. Check UART baud rate (must be 115200)
2. Test with different terminal program
3. Verify TX/RX pins (PA9, PA10)
4. Reset the board

### Frequency too high/low?
The formula for ARR calculation:
```c
ARR = (SystemClock / (Prescaler + 1)) / Frequency
ARR = (4000000 / 4) / Frequency
ARR = 1000000 / Frequency
```

## License

See [LICENSE](../LICENSE) file in the root directory.

## Author

Maximilian Lell  
Created: July 2025

## Acknowledgments

- [EmbeddedCli Library](https://github.com/funbiscuit/embedded-cli)
- STM32 HAL Library
- MikroElektronika for BUZZ 3 Click documentation

