import matplotlib.pyplot as plt
import numpy as np
import serial
import sys
import os

port = "/dev/ttyACM0"
baudrate = 1250000
YELLOW = "\033[33m"
RESET = "\033[0m"
initial_values = {}


def clear_screen():
    if os.name == "nt":
        os.system("cls")
    else:
        print("\033[2J\033[H", end="")


try:
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Serial port {port} opened successfully.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    sys.exit(1)

plt.ion()
fig = plt.figure(figsize=(12, 6))
ax = fig.add_subplot(111)
plt.ylim([0, 800])
plt.xlim([0, 50])

ax.legend();

data1 = np.zeros(10)
data2 = np.zeros(10)
data3 = np.zeros(10)

received_data1 = 0;
received_data2 = 0;
received_data3 = 0;

label1 = ""
label2 = ""
label3 = ""

(line1,) = ax.plot(data1, color="r", label=label1)
(line2,) = ax.plot(data2, color="g", label=label2)
(line3,) = ax.plot(data3, color="b", label=label3)


ax.set_xlabel("Time")
ax.set_ylabel("Value")
ax.set_title("SERIAL DATA GRAPH")

try:
    while True:
        if ser.in_waiting > 0:
            line_input = ser.readline().decode("utf-8").rstrip()
            # clear_screen()

            dizi = line_input.split(",")
            for index, item in enumerate(dizi):
                try:
                    key, value = item.split(":")
                    
                    value = int(value.strip())
                    
                    if index == 0:
                        label1 = key
                        received_data1 = value;
                        data1 = np.append(data1, value)
                        if len(data1) > 400:
                            data1 = data1[-400:]
                        line1.set_ydata(data1)
                        line1.set_xdata(np.arange(len(data1)))
                        ax.set_xlim(0, len(data1))
                    
                    elif index == 1:
                        label2 = key
                        received_data2 = value;
                        data2 = np.append(data2, value)
                        if len(data2) > 400:
                            data2 = data2[-400:]
                        line2.set_ydata(data2)
                        line2.set_xdata(np.arange(len(data2)))
                        ax.set_xlim(0, len(data2))
                    
                        
                    elif index == 2:
                        label3 = key
                        received_data3 = value;
                        data3 = np.append(data3, value)
                        if len(data3) > 400:
                            data3 = data3[-400:]
                        line3.set_ydata(data3)
                        line3.set_xdata(np.arange(len(data3)))
                        ax.set_xlim(0, len(data3))
                    
                    line1.set_label(label1);
                    line2.set_label(label2);
                    line3.set_label(label3);
                    
                    ax.legend();
                    
                    plt.draw()
                    plt.pause(0.001)
                    
                    
                    # if key in initial_values:
                    #     if initial_values[key] != value:
                    #         print(f"{key}: {YELLOW}{value}{RESET}")
                    #         initial_values[key] = value
                    #     else:
                    #         print(f"{key}: {value}")
                    # else:
                    #     initial_values[key] = value
                    #     print(f"{key}: {value}")


                except ValueError:
                    print(f"Invalid data format: {item}")
                    
                    
except KeyboardInterrupt:
    print("\nExiting...")
finally:
    ser.close()
    plt.ioff()
    plt.close()
