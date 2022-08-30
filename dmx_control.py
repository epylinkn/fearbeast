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
        
        self.dmx = Controller('/dev/ttyUSB0')  # Typical of Linux
        # self.dmx = Controller('/dev/ttyAMA0')  # Typical of Linux
        print(self.dmx)

        # dmx.set_channel(1, 255)  # Sets DMX channel 1 to max 255
        # dmx.submit()  # Sends the update to the controller
        
        print("Here")
        # self._set_channels(True, 100)
        # self.dmx.submit()  # Sends the update to the controller

    # TO BEASt
    def fade_to_fearing(self, progress):
        self._set_channels(True, progress)
        self.dmx.submit()
        
    # TO CHILD
    def fade_to_parting(self, progress):
        self._set_channels(False, progress)
        self.dmx.submit()
        
    def test(self, start_channel):
        for i in range(start_channel, start_channel + 10):
            self.dmx.set_channel(i, 255)  # Sets DMX channel 1 to max 255
        self.dmx.submit()
            

    
    # == PRIVATE METHODS == 

    def _set_channels(self, isFearing, progress):
        for channel in self.universe:
            # NB. non-DMX key value data b/c JSON doesn't allow comments...
            if channel.find("ID") >= 0:
                continue

            partingValue = self.universe[channel][0]
            fearValue = self.universe[channel][1]
            
            if isFearing:
                value = self._interpolate(partingValue, fearValue, progress)
            else:
                value = self._interpolate(fearValue, partingValue, progress)
                
            channel = int(channel)
            # if channel >= 285 and channel < 295:
                # print(f"Channel: {channel}, Value: {value}")
            self.dmx.set_channel(channel, value)  # Sets DMX channel 1 to max 255
        
    def _interpolate(self, startByte, endByte, progress):
        distance = int(endByte - startByte)
        step = floor(distance * progress / 100)

        if distance == 0:
            value = startByte
        else: # do the math if there is a change
            value = startByte + step

        # print(f"value: {value}, step: {step}, progress: {progress}, startByte: {startByte}")
        set_value = self._constrain_byte(value)
        return set_value
            
    def _constrain_byte(self, value):
        if value > 255:
            return 255
        if value < 0:
            return 0
            
        return value
