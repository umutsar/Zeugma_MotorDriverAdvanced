import serial
import sys
import os

port = '/dev/ttyACM0'
baudrate = 250000

YELLOW = "\033[33m"
RESET = "\033[0m"

initial_values = {}

def clear_screen():
    if os.name == 'nt':
        os.system('cls')
    else:
        print("\033[2J\033[H", end='')

try:
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Serial port {port} opened successfully.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    sys.exit(1)

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            
            clear_screen()
            
            dizi = line.split(",")
            for item in dizi:
                key, value = item.split(":")
                value = value.strip() 

                if key in initial_values:
                    if initial_values[key] != value:
                        print(f"{key}: {YELLOW}{value}{RESET}")
                        initial_values[key] = value 
                    else:
                        print(f"{key}: {value}")
                else:
                    initial_values[key] = value 
                    print(f"{key}: {value}")

except KeyboardInterrupt:
    print("\nExiting...")
    
finally:
    ser.close()
