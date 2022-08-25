from DMXEnttecPro import Controller
import json
import time
import threading


#This isn't ready, will work on next
class Lights:
    def __init__(self):
        return
        l = open('lighting_changes.json')
        fixtures = json.load(l)
        self.fixtures = fixtures
        
        self.dmx = Controller('/dev/ttyUSB0')  # Typical of Linux
        # self.dmx = Controller('/dev/ttyAMA0')  # Typical of Linux
        # dmx.set_channel(1, 255)  # Sets DMX channel 1 to max 255
        # dmx.submit()  # Sends the update to the controller
        self.set_channels(1, 1, False)
        self.dmx.submit()  # Sends the update to the controller

    
    def set_channels(self, max_steps, step, activate):
        return
        fixtures = self.fixtures["fixtures"]
        set_channel = 0
        for f in fixtures:
            light = str(f)
            # print(f"light is {light}")
            fixture = fixtures[light]
            # print(f"fixture is {fixture}")
            for channel in fixture:
                set_channel += 1
                # print(f"channel is:{channel}")
                start_end = fixture[channel]
                distance = int(abs(start_end[1] - start_end[0]))
                # print(f"distance is {distance}")
                if distance == 0: # when the start and end value is the same, then set that the value to the start value, otherwise it becomes 0
                    set_value = (int(start_end[0]))
                else: # do the math if there is a change
                    step_distance = ((distance/max_steps))
                    print(f"step distance:{step_distance}")
                    if activate: # will go from start value to end value
                        # print(f"set_value = {step} * {step_distance})")
                        set_value = step * step_distance
                        # print(f"set_value is:{set_value}")
                        # if step == max_steps:
                        #     set_value = start_end[1]
                    else: # will go from end value to start value
                        set_value = (max_steps - step) * step_distance
                        # if step == max_steps:
                        #     set_value = start_end[0]
                    # print(f"step distance is {step_distance}")
                if set_value > 255:
                    set_value = 255
                elif set_value < 0:
                    set_value = 0
                set_value = int(set_value)

                print(f"Set Channel: {set_channel}, Set Value: {set_value}")
                self.dmx.set_channel(set_channel, set_value)  # Sets DMX channel 1 to max 255
        
    def light_fade(self, activate = False):
        return
        step = 1
        max_steps = 40
        old_time = time.time()
        for s in range(max_steps + 1):
            self.set_channels(max_steps, step, activate)
        
                
            # print(f"step is:{step}")
            self.dmx.submit()  # Sends the update to the controller
            step+= 1
            # print(f"sleep time: {(1.5/max_steps)}")
            time.sleep(1.5/max_steps)
            # current_time = time.time()
            # print(f"current_time {current_time}")
            # try:
            #     wait_time = (float(current_time) - float(old_time))
            #     # print(f"wait time is {wait_time}")
            #     old_time = current_time
            # except Exception as err:
            #     print(f"wait time error {err}")
            #     # print(f"start_end of channel are {start_end}")
            # #     print(self.fixtures["fixtures"][str(light)])
        #     set_value = start_end[1]
        # if activate:
        #     print("in activate")
        #     self.set_channels(1, 1, True)
        # else:
        #     print("in deactivate")
        #     self.set_channels(1, 1, False)
        # self.dmx.submit()  # Sends the update to the controller
