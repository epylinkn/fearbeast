from dmx_control import Lights
from trigger_control import Trigger
import time

def init():
    lights = Lights()

    try:
        trigger = Trigger(lights)
    except Exception as err:
        print(f"Problem starting trigger: {err}")

print("Starting ~/Fearbeast/init.py")
init()
