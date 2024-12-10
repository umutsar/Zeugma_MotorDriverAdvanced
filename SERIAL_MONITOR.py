import serial
import sys
import os

# Seri port ve baudrate ayarları
port = '/dev/ttyACM0'
baudrate = 250000

# Sarı renkte yazdırmak için ANSI kaçış kodları
YELLOW = "\033[33m"
RESET = "\033[0m"

# İlk değerleri tutmak için bir sözlük
initial_values = {}

# Ekranı temizlemek için fonksiyon
def clear_screen():
    if os.name == 'nt':
        os.system('cls')
    else:
        print("\033[2J\033[H", end='')

# Seri portu açma işlemi
try:
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Serial port {port} opened successfully.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    sys.exit(1)

try:
    while True:
        # Yeni verinin gelip gelmediğini kontrol et
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            
            clear_screen()
            
            # Anahtar-değer çiftlerini ayır
            dizi = line.split(",")
            for item in dizi:
                key, value = item.split(":")
                value = value.strip()  # Gereksiz boşlukları sil

                # Değer değişmiş mi kontrol et
                if key in initial_values:
                    if initial_values[key] != value:
                        print(f"{key}: {YELLOW}{value}{RESET}")  # Değişmişse sarı renkte yaz
                        initial_values[key] = value  # Yeni değeri kaydet
                    else:
                        print(f"{key}: {value}")  # Değişmemişse normal yaz
                else:
                    initial_values[key] = value  # İlk kez görüyorsak kaydet
                    print(f"{key}: {value}")  # İlk değerler normal yazılır

except KeyboardInterrupt:
    print("\nExiting...")
    
finally:
    ser.close()
