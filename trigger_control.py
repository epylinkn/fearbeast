import threading
import time
import serial

class Trigger:
    def __init__(self, lights):
        self.lights = lights

        self.ard = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        self.ard.reset_input_buffer()

        # Start a listener thread as to not block up the rest of the software
        l = threading.Thread(target=self.listen, args=())
        l.start()
    
    def listen(self):
        print("starting trigger listen")

        while True:
            if self.ard.in_waiting > 0:
                line = self.ard.readline().decode('utf-8').rstrip()
                print(line)
                if line == "ACTIVATED":
                    if not active:
                        active = True
                        self.lights.light_fade(True)
                        time.sleep(1)
                if line == "DEACTIVATED":
                    if active:
                        active = False
                        self.lights.light_fade(False)
                        time.sleep(1)
