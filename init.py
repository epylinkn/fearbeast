from dmx_control import Lights
from trigger_control import Trigger
import time

def init():
    print("prelghts")
    lights = Lights()
    print("iightst instatniated")

    try:
        trigger = Trigger(lights)
        print("trgger success?")
    except Exception as err:
        print(f"Problem starting trigger: {err}")

print("Starting ~/fearbeast/init.py")
init()
