import pygame
import os
import time

class Audio:
    def __init__(self):
        #init all the things needed for audio
        pygame.init()
        pygame.mixer.pre_init(44100, -16, 1, 2048)
        pygame.mixer.init()
        time.sleep(1)


    def play(self, asset):
        
        # which asset is being used?
        # print(asset)
        # make the path relative to where this program is running
        path = os.path.dirname(os.path.realpath(__file__))

        # print(f"path is:{path}")
        # print(f"asset is:{asset}")
        # print(f"pygame.mixer.Sound.play({asset})")
        try:
            # print("fading out")
            # fade out sounds before starting the next sound
            pygame.mixer.fadeout(1500)
            # setup the sound to play
            sound = pygame.mixer.Sound("{}/{}".format(path, asset))
            # print(f"sound is {asset}")
            # play the sound
            pygame.mixer.Sound.play(sound, loops=-1, maxtime=0, fade_ms=1500)
        except Exception as err:
            print(f"Audio asset {asset} play failure: {err}")