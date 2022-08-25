import pygame
from audio_control import Audio
from dmx_control import Lights
from trigger_control import Trigger
import time

def init():
    # setup the audio class to pass into the trigger class
    audio = Audio()
    lights = Lights()
    try:
        # passing in audio into the trigger
        trigger = Trigger(audio, lights)
    except Exception as err:
        print(f"Problem starting trigger: {err}")

#### this is simply here as a test
# def cycle_play(audio):
#     childMusic = "TheParting.wav"
#     beastMusic = "SCP-x3x.wav"
#     print(beastMusic)
#     print(childMusic)
#     while True:
#         audio.play("SCP-x3x.wav")
#         time.sleep(10)
#         audio.play("TheParting.wav")
#         time.sleep(10)

print("Starting ~/Fearbeast/init.py")
init()
