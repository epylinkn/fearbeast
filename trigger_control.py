from operator import truediv
import threading
import time
import serial

class Trigger:
    def __init__(self, lights):
        print("foo")
        self.lights = lights

        self.ard = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        self.ard.reset_input_buffer()
        
        print(self.ard)

        # Start a listener thread as to not block up the rest of the software
        l = threading.Thread(target=self.listen, args=())
        l.start()
    
    def listen(self):
        print("starting trigger listen")
        chan = 200
        progress = 0
        isBeasting = True
        prevState = "foo"


        while True:
            # 1. Check for state change
            if self.ard.in_waiting > 0:
                line = self.ard.readline().decode('utf-8').rstrip()
                if line != prevState:
                    print(line)
                    prevState = line

                if line == "TO_CHILD" and isBeasting:
                    isBeasting = False
                    progress = 0
                
                if line == "TO_BEAST" and not isBeasting:
                    isBeasting = True
                    progress = 0
                        
            
            # Skip if not transititoning, else progress
            if progress > 100:
                continue

            # # # 2. Animate lights
            if isBeasting:
                self.lights.fade_to_fearing(progress)
                progress = progress + 0.3
                time.sleep(0.03)
            else:
                self.lights.fade_to_parting(progress)
                progress = progress + 0.5
                time.sleep(0.03)
            
