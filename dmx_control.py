from DMXEnttecPro import Controller
import json
import time
import threading
from math import floor


#This isn't ready, will work on next
class Lights:
    def __init__(self):
        f = open('fixtures.json')
        config = json.load(f)
        self.universe = config["universe"]
        self.isFearing = True
        
        self.dmx = Controller('/dev/ttyUSB0')  # Typical of Linux
        # self.dmx = Controller('/dev/ttyAMA0')  # Typical of Linux

        # dmx.set_channel(1, 255)  # Sets DMX channel 1 to max 255
        # dmx.submit()  # Sends the update to the controller
        self.set_channels(1, 7, False)
        self.dmx.submit()  # Sends the update to the controller
        
    def interpolate(self, startByte, endByte, progress):
        distance = int(startByte - endByte)

        if distance == 0:
            value = startByte
        else: # do the math if there is a change
            step = floor(distance * progress)
            print(f"step distance: {step}")
            value = startByte + step

        set_value = self.constrain_byte(value)
        print(f"Interpolated Value: {set_value}")
        return set_value
            
    def constrain_byte(self, value):
        if value > 255:
            return 255
        if value < 0:
            return 0
            
        return value
    
    def set_channels(self, min, max, activate):
        for channel in self.universe:
            fearValue = self.universe[channel][0]
            partingValue = self.universe[channel][1]
            
            # TODO: which way are we transitioning...
            if activate:
                # self.isFearing = False
                value = self.interpolate(partingValue, fearValue, 1.00)
            else:
                # self.isFearing = True
                value = self.interpolate(fearValue, partingValue, 1.00)
                
            channel = int(channel)
            print(f"Set Channel --- Channel: {channel}, Value: {value}")
            self.dmx.set_channel(channel, value)  # Sets DMX channel 1 to max 255
            
    def light_fade(self, activate = False):
        self.set_channels(1, 7, activate)
        self.dmx.submit()

        # step = 1
        # max_steps = 40
        # old_time = time.time()
        # for s in range(max_steps + 1):
        #     self.set_channels(max_steps, step, activate)
        
                
        #     # print(f"step is:{step}")
        #     self.dmx.submit()  # Sends the update to the controller
        #     step+= 1
        #     # print(f"sleep time: {(1.5/max_steps)}")
        #     time.sleep(1.5/max_steps)
        #     # current_time = time.time()
        #     # print(f"current_time {current_time}")
        #     # try:
        #     #     wait_time = (float(current_time) - float(old_time))
        #     #     # print(f"wait time is {wait_time}")
        #     #     old_time = current_time
        #     # except Exception as err:
        #     #     print(f"wait time error {err}")
        #     #     # print(f"start_end of channel are {start_end}")
        #     # #     print(self.fixtures["fixtures"][str(light)])
        # #     set_value = start_end[1]
        # # if activate:
        # #     print("in activate")
        # #     self.set_channels(1, 1, True)
        # # else:
        # #     print("in deactivate")
        # #     self.set_channels(1, 1, False)
        # # self.dmx.submit()  # Sends the update to the controller
