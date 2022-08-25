import RPi.GPIO as GPIO
import threading
import time
import serial
class Trigger:
    def __init__(self, audio, lights):
        self.audio = audio
        self.lights = lights

        self.activateAudio = "TheParting.wav"
        self.deactivateAudio = "SCP-x3x.wav"
        
        self.ard = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        self.ard.reset_input_buffer()

        # Start a listener thread as to not block up the rest of the software
        l = threading.Thread(target=self.listen, args=())
        l.start()
    
    def listen(self):
        print("starting trigger listen")
        self.audio.play(self.activateAudio)
        # "active" boolean used to gate the trigger
        active = False
        while True:
            if self.ard.in_waiting > 0:
                line = self.ard.readline().decode('utf-8').rstrip()
                print(line)
                if line == "ACTIVATED":
                    if not active:
                        # print("Button was pushed!")
                        active = True
                        self.audio.play(self.activateAudio)
                        self.lights.light_fade(True)
                        time.sleep(1)
                if line == "DEACTIVATED":
                    if active:
                        # print("Button was released")
                        active = False
                        self.audio.play(self.deactivateAudio)
                        self.lights.light_fade(False)
                        # self.lights.deactivate()
                        time.sleep(1)
                    
            # time.sleep(10)
            # time.sleep(10)

            # events = pygame.event.get()
            # for event in events:
            #     print(f"events {event}")
            #     if event.type == pygame.KEYDOWN:
            #         if event.key == pygame.K_UP:
            #             print("space down")
            #             self.audio.play("TheParting.wav")
            #     if event.type == pygame.KEYUP:
            #         if event.key == pygame.K_UP:
            #             print("space up")
            #             self.audio.play("SCP-x3x.wav")
