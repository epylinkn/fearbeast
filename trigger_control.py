from operator import truediv
import threading
import time
import serial

class Trigger:
    def __init__(self, lights):
        self.lights = lights

        # self.ard = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        # self.ard.reset_input_buffer()

        # Start a listener thread as to not block up the rest of the software
        l = threading.Thread(target=self.listen, args=())
        l.start()
    
    def listen(self):
        print("starting trigger listen")
        isFearing = True
        progress = 0
        counter = 262

        while True:
            # print(counter)
            # self.lights.test(counter)
            # counter += 1
            self.lights.fade_to_fearing(100)
            time.sleep(3)
            self.lights.fade_to_parting(100)
            time.sleep(5)



            # # 1. Check for state change
            # if self.ard.in_waiting > 0:
            #     line = self.ard.readline().decode('utf-8').rstrip()
            #     print(line)
            #     if line == "ACTIVATED" and isFearing:
            #         isFearing = False
            #         progress = 0
                        
            #     if line == "DEACTIVATED" and not isFearing:
            #         isFearing = True
            #         progress = 0
            
            # # Skip if not transititoning, else progress
            # if progress > 100:
            #     continue
            # progress = progress + 0.3

            # # 2. Animate lights
            # if isFearing:
            #     self.lights.fade_to_fearing(progress)
            #     time.sleep(0.01)
            # else:
            #     self.lights.fade_to_parting(progress)
            #     time.sleep(0.01)
            
