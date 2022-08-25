import serial

# class Arduino:
    # def __init__(self):
if __name__ == '__main__':
    ard = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    ard.reset_input_buffer()
    while True:
        if ard.in_waiting > 0:
            line = ard.readline().decode('utf-8').rstrip()
            print(line)
